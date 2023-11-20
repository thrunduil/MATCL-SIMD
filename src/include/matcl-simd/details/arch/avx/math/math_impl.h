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

namespace matcl { namespace simd { namespace details
{

//-----------------------------------------------------------------------
//                          pow2k
//-----------------------------------------------------------------------
template<class Val>
struct simd_pow2k<Val, 256, avx_tag>
{
    using simd_type = simd<Val, 256, avx_tag>;
    using int_type  = typename details::integer_type<Val>::type;
    using simd_int  = simd<int_type, 256, avx_tag>;

    force_inline
    static simd_type eval(const simd_type& k)
    {
        return simd_pow2k_impl<Val, 256, avx_tag>::eval(k);
    };

    force_inline
    static simd_type eval_i(const simd_int& k)
    {
        return simd_pow2k_impl<Val, 256, avx_tag>::eval_i(k);
    };
};

//-----------------------------------------------------------------------
//                          exponent
//-----------------------------------------------------------------------
template<class Val>
struct simd_exponent<Val, 256, avx_tag>
{
    using simd_type = simd<Val, 256, avx_tag>;
    using int_type  = typename details::integer_type<Val>::type;
    using simd_int  = simd<int_type, 256, avx_tag>;

    force_inline
    static simd_type eval(const simd_type& k)
    {
        return simd_exponent_impl<Val, 256, avx_tag>::eval(k);
    };

    force_inline
    static simd_int eval_i(const simd_type& k)
    {
        return simd_exponent_impl<Val, 256, avx_tag>::eval_i(k);
    };
};

//-----------------------------------------------------------------------
//                          copysign
//-----------------------------------------------------------------------
template<class Val>
struct simd_copysign<Val, 256, avx_tag>
{
    using simd_type = simd<Val, 256, avx_tag>;

    force_inline
    static simd_type eval(const simd_type& x, const simd_type& y)
    {
        return simd_copysign_impl<Val, 256, avx_tag>::eval(x, y);
    };
};

//-----------------------------------------------------------------------
//                          fraction
//-----------------------------------------------------------------------
template<class Val>
struct simd_fraction<Val, 256, avx_tag>
{
    using simd_type = simd<Val, 256, avx_tag>;
    using int_type  = typename details::integer_type<Val>::type;
    using simd_int  = simd<int_type, 256, avx_tag>;

    force_inline
    static simd_type eval(const simd_type& k)
    {
        return simd_fraction_impl<Val, 256, avx_tag>::eval(k);
    };
};

}}}
