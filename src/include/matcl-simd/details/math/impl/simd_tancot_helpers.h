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
#include "matcl-simd/details/math/impl/simd_sincos_helpers.h"

#pragma warning(push)
#pragma warning(disable: 4127)  //conditional expression is constant

namespace matcl { namespace simd { namespace details
{

//-----------------------------------------------------------------------
//                        UTILS
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
//                              DOUBLE-FLOAT
//-----------------------------------------------------------------------

static const int tan_tag    = 0;
static const int cot_tag    = 1;

template<class Val, int Bits, class Tag, 
         bool Is_scalar = is_scalar_tag<Tag>::value>
struct simd_tancot_reconstruction
{
    using simd_type         = ms::simd<Val, Bits, Tag>;

    static const
    int int_vec_size        = std::max(simd_type::vector_size, 4);
    using simd_int          = typename ms::default_simd_vector_size<int32_t, int_vec_size>::type;
    using equiv_int         = typename integer_type<Val>::type;
    using simd_int_eq       = ms::simd<equiv_int, Bits, Tag>;

    template<int Version>
    force_inline
    static simd_type eval(const simd_int& qi, const simd_type& pt, const simd_type& pc)
    {
        // tan(x + k * pi/2) = tan(x + [4 k1 + k2] * pi/2) = tan(x + k2 * pi/2)
        //      = tan(x)    for k2 = 0
        //      = -cot(x)   for k2 = 1
        //      = tan(x)    for k2 = 2
        //      = -cot(x)   for k2 = 3
        // cot(x + k * pi/2)
        //      = cot(x)    for k2 = 0
        //      = -tan(x)   for k2 = 1
        //      = cot(x)    for k2 = 2
        //      = -tan(x)   for k2 = 3

        simd_int_eq q       = convert_int32<simd_int, simd_int_eq>::eval(qi);
        simd_int_eq swap    = neq(bitwise_and(q, simd_int_eq(1)), simd_int_eq::zero());

        simd_type res;
        if (Version == tan_tag)
            res             = if_then_else(reinterpret_as<Val>(swap), -pc, pt);
        else
            res             = if_then_else(reinterpret_as<Val>(swap), -pt, pc);

        return res;
    }
};

template<class Val, int Bits, class Tag>
struct simd_tancot_reconstruction<Val, Bits, Tag, true>
{
    using simd_type         = ms::simd<Val, Bits, Tag>;
    using simd_int          = typename ms::simd<int32_t, Bits, Tag>::simd_half;
    using equiv_int         = typename integer_type<Val>::type;
    using simd_int_eq       = ms::simd<equiv_int, Bits, Tag>;

    template<int Version>
    force_inline
    static simd_type eval(const simd_int& qi, const simd_type& pt, const simd_type& pc)
    {
        // tan(x + k * pi/2) = tan(x + [4 k1 + k2] * pi/2) = tan(x + k2 * pi/2)
        //      = tan(x)    for k2 = 0
        //      = -cot(x)   for k2 = 1
        //      = tan(x)    for k2 = 2
        //      = -cot(x)   for k2 = 3
        // cot(x + k * pi/2)
        //      = cot(x)    for k2 = 0
        //      = -tan(x)   for k2 = 1
        //      = cot(x)    for k2 = 2
        //      = -tan(x)   for k2 = 3

        simd_int_eq q       = convert_int32<simd_int, simd_int_eq>::eval(qi);
        simd_int_eq swap    = neq(bitwise_and(q, simd_int_eq(1)), simd_int_eq::zero());

        simd_type res;
        if (Version == tan_tag)
            res             = if_then_else(reinterpret_as<Val>(swap), -pc, pt);
        else
            res             = if_then_else(reinterpret_as<Val>(swap), -pt, pc);

        return res;
    }
};

}}}

#pragma warning(pop)