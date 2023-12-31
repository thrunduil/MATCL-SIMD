/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/details/arch/simd_impl.h"
#include "matcl-simd/details/math/simd_math_func_def.h"
#include "matcl-simd/poly/poly_eval.h"
#include "matcl-simd/details/float/twofold.h"
#include "matcl-simd/details/math/impl/payne_hanek.inl"

#pragma warning(push)
#pragma warning(disable: 4127)  //conditional expression is constant

namespace matcl { namespace simd { namespace details
{

//-----------------------------------------------------------------------
//                        UTILS
//-----------------------------------------------------------------------

template<class Simd_int32, class Simd_int64>
struct convert_int32
{};

template<class Simd_int32>
struct convert_int32<Simd_int32, Simd_int32>
{
    force_inline
    static Simd_int32 eval(const Simd_int32& x)
    {
        return x;
    }
};

template<>
struct convert_int32<simd<int32_t, 128, scalar_nosimd_tag>, simd<int64_t, 128, scalar_nosimd_tag>>
{
    using simd32    = simd<int32_t, 128, scalar_nosimd_tag>;
    using simd64    = simd<int64_t, 128, scalar_nosimd_tag>;

    force_inline
    static simd64 eval(const simd32& x)
    {
        return x.convert_to_int64();
    }
};

#if MATCL_ARCHITECTURE_HAS_SSE2
    template<>
    struct convert_int32<simd<int32_t, 128, sse_tag>, simd<int64_t, 128, sse_tag>>
    {
        using simd32    = simd<int32_t, 128, sse_tag>;
        using simd64    = simd<int64_t, 128, sse_tag>;

        force_inline
        static simd64 eval(const simd32& x)
        {
            return x.convert_low_to_int64();
        }
    };

    template<>
    struct convert_int32<simd<int32_t, 128, scalar_sse_tag>, simd<int64_t, 128, scalar_sse_tag>>
    {
        using simd32    = simd<int32_t, 128, scalar_sse_tag>;
        using simd64    = simd<int64_t, 128, scalar_sse_tag>;

        force_inline
        static simd64 eval(const simd32& x)
        {
            return x.convert_to_int64();
        }
    };
#endif

#if MATCL_ARCHITECTURE_HAS_AVX
    template<>
    struct convert_int32<simd<int32_t, 128, sse_tag>, simd<int64_t, 256, avx_tag>>
    {
        using simd32    = simd<int32_t, 128, sse_tag>;
        using simd64    = simd<int64_t, 256, avx_tag>;

        force_inline
        static simd64 eval(const simd32& x)
        {
            return x.convert_to_int64();
        }
    };
#endif

template<class T>
struct get_mask_sign{};

template<>
struct get_mask_sign<int32_t>
{
    static const int32_t value = int32_t(uint32_t(1) << 31);
};

template<>
struct get_mask_sign<int64_t>
{
    static const int64_t value = int64_t(uint64_t(1) << 63);
};

//-----------------------------------------------------------------------
//                      DOUBLE-FLOAT SIN-COS
//-----------------------------------------------------------------------

static const int sin_tag    = 0;
static const int cos_tag    = 1;

template<class Val, int Bits, class Tag, 
         bool Is_scalar = is_scalar_tag<Tag>::value>
struct simd_sincos_reconstruction
{
    using simd_type         = ms::simd<Val, Bits, Tag>;

    static const
    int int_vec_size        = std::max(simd_type::vector_size, 4);
    using simd_int          = typename ms::default_simd_vector_size<int32_t, int_vec_size>::type;
    using equiv_int         = typename integer_type<Val>::type;
    using simd_int_eq       = ms::simd<equiv_int, Bits, Tag>;

    template<int Version>
    force_inline
    static simd_type eval(const simd_int& qi, const simd_type& pc, const simd_type& ps)
    {
        // sin(x + k * pi/2) = sin(x + [4 k1 + k2] * pi/2) = sin(x + k2 * pi/2)
        //      = cos(k2 * pi/2) * sin(x) + sin(k2 * pi/2) * cos(x)
        // cos(x + k * pi/2)
        //      = cos(k2 * pi/2) * cos(x) - sin(k2 * pi/2) * sin(x)

        static const equiv_int mask_sign    = get_mask_sign<equiv_int>::value;

        simd_int_eq q       = convert_int32<simd_int, simd_int_eq>::eval(qi);
        simd_int_eq swap    = neq(bitwise_and(q, simd_int_eq(1)), simd_int_eq::zero());

        simd_type res;
        simd_int_eq swap_sign;
        simd_int_eq sign_mask;

        if (Version == sin_tag)
        {
            //swap sign for q = 2, 3
            swap_sign       = neq(bitwise_and(q, simd_int_eq(2)), simd_int_eq::zero());
            sign_mask       = bitwise_and(swap_sign, simd_int_eq(mask_sign));

            res             = if_then_else(reinterpret_as<Val>(swap), pc, ps);
        }
        else
        {
            //swap sign for q = 1, 2
            swap_sign       = neq(bitwise_and(q + simd_int_eq::one(), simd_int_eq(2)), simd_int_eq::zero());
            sign_mask       = bitwise_and(swap_sign, simd_int_eq(mask_sign));

            res             = if_then_else(reinterpret_as<Val>(swap), ps, pc);
        };

        res                 = bitwise_xor(res, reinterpret_as<Val>(sign_mask));
        return res;
    }

    force_inline
    static void eval_both(const simd_int& qi, const simd_type& pc, const simd_type& ps,
                    simd_type& res_s, simd_type& res_c)
    {
        // sin(x + k * pi/2) = sin(x + [4 k1 + k2] * pi/2) = sin(x + k2 * pi/2)
        //      = cos(k2 * pi/2) * sin(x) + sin(k2 * pi/2) * cos(x)
        // cos(x + k * pi/2)
        //      = cos(k2 * pi/2) * cos(x) - sin(k2 * pi/2) * sin(x)

        static const equiv_int mask_sign    = get_mask_sign<equiv_int>::value;

        simd_int_eq q       = convert_int32<simd_int, simd_int_eq>::eval(qi);
        simd_int_eq swap    = neq(bitwise_and(q, simd_int_eq(1)), simd_int_eq::zero());

        simd_int_eq swap_sign_sin, swap_sign_cos;

        //swap sign for q = 2, 3
        swap_sign_sin   = neq(bitwise_and(q, simd_int_eq(2)), simd_int_eq::zero());

        //swap sign for q = 1, 2
        swap_sign_cos   = neq(bitwise_and(q + simd_int_eq::one(), simd_int_eq(2)), 
                            simd_int_eq::zero());

        simd_int_eq sign_mask_sin, sign_mask_cos;

        sign_mask_sin   = bitwise_and(swap_sign_sin, simd_int_eq(mask_sign));
        sign_mask_cos   = bitwise_and(swap_sign_cos, simd_int_eq(mask_sign));

        res_s           = if_then_else(reinterpret_as<Val>(swap), pc, ps);
        res_c           = if_then_else(reinterpret_as<Val>(swap), ps, pc);

        res_s           = bitwise_xor(res_s, reinterpret_as<Val>(sign_mask_sin));
        res_c           = bitwise_xor(res_c, reinterpret_as<Val>(sign_mask_cos));
    }
};

template<class Val, int Bits, class Tag>
struct simd_sincos_reconstruction<Val, Bits, Tag, true>
{
    using simd_type         = ms::simd<Val, Bits, Tag>;
    using simd_int          = typename ms::simd<int32_t, Bits, Tag>::simd_half;

    template<int Version>
    force_inline
    static simd_type eval(const simd_int& q, const simd_type& pc, const simd_type& ps)
    {
        // sin(x + k * pi/2) = sin(x + [4 k1 + k2] * pi/2) = sin(x + k2 * pi/2)
        //      = cos(k2 * pi/2) * sin(x) + sin(k2 * pi/2) * cos(x)
        // cos(x + k * pi/2)
        //      = cos(k2 * pi/2) * cos(x) - sin(k2 * pi/2) * sin(x)

        const Val cos_table[]   = {1.0, 0.0, -1.0, 0.0};
        const Val sin_table[]   = {0.0, 1.0, 0.0, -1.0};
        
        simd_type coef_cos      = simd_type(cos_table[q.first()]);
        simd_type coef_sin      = simd_type(sin_table[q.first()]);

        if (Version == sin_tag)
        {
            simd_type ret   =  fma_f(coef_sin, pc, coef_cos * ps);
            return ret;
        }
        else
        {
            simd_type ret   = fnma_f(coef_sin, ps, coef_cos * pc);
            return ret;
        };
    }
};

}}}

#pragma warning(pop)