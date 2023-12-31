/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/details/arch/simd_impl.h"
#include "matcl-simd/details/func/simd_func_def.h"
#include "matcl-simd/details/scalar_func.h"
#include "matcl-simd/details/float/fma_dekker_simd.inl"

namespace matcl { namespace simd { namespace details
{

template<class T>
struct simd_reverse<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x)
    {
        return simd_type(reverse(x.data[1]), reverse(x.data[0]));
    };
};

template<class T>
struct simd_mult<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x, const simd_type& y)
    {
        return simd_type(x.data[0] * y.data[0], x.data[1] * y.data[1]);
    };
};

template<class T>
struct simd_div<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x, const simd_type& y)
    {
        return simd_type(x.data[0] / y.data[0], x.data[1] / y.data[1]);
    };
};

template<class T>
struct simd_plus<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x, const simd_type& y)
    {
        return simd_type(x.data[0] + y.data[0], x.data[1] + y.data[1]);
    };
};

template<class T>
struct simd_minus<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x, const simd_type& y)
    {
        return simd_type(x.data[0] - y.data[0], x.data[1] - y.data[1]);
    };
};

template<class T>
struct simd_uminus<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x)
    {
        return simd_type(-x.data[0], -x.data[1]);
    };
};

template<class T>
struct simd_horizontal_sum<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static T eval(const simd_type& x)
    {
        return horizontal_sum(x.data[0] + x.data[1]);
    };
};

template<class T>
struct simd_horizontal_min<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static T eval(const simd_type& x)
    {
        return horizontal_min(min(x.data[0], x.data[1]));
    };
};

template<class T>
struct simd_horizontal_max<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static T eval(const simd_type& x)
    {
        return horizontal_max(max(x.data[0], x.data[1]));
    };
};

template<class T>
struct simd_sub_add<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x, const simd_type& y)
    {
        return simd_type(sub_add(x.data[0], y.data[0]), sub_add(x.data[1], y.data[1]));
    };
};

template<class T>
struct simd_fma_f<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x, const simd_type& y, const simd_type& z)
    {
        return simd_type(fma_f(x.data[0], y.data[0], z.data[0]), 
                         fma_f(x.data[1], y.data[1], z.data[1]));
    };
};

template<class T>
struct simd_fms_f<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x, const simd_type& y, const simd_type& z)
    {
        return simd_type(fms_f(x.data[0], y.data[0], z.data[0]), 
                         fms_f(x.data[1], y.data[1], z.data[1]));
    };
};

//
template<class T>
struct simd_fnma_f<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x, const simd_type& y, const simd_type& z)
    {
        return simd_type(fnma_f(x.data[0], y.data[0], z.data[0]), 
                         fnma_f(x.data[1], y.data[1], z.data[1]));
    };
};

template<class T>
struct simd_fnms_f<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x, const simd_type& y, const simd_type& z)
    {
        return simd_type(fnms_f(x.data[0], y.data[0], z.data[0]), 
                         fnms_f(x.data[1], y.data[1], z.data[1]));
    };
};

template<class T>
struct simd_fma_a<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x, const simd_type& y, const simd_type& z)
    {
        return simd_type(fma_a(x.data[0], y.data[0], z.data[0]), 
                         fma_a(x.data[1], y.data[1], z.data[1]));
    };
};

template<class T>
struct simd_fms_a<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x, const simd_type& y, const simd_type& z)
    {
        return simd_type(fms_a(x.data[0], y.data[0], z.data[0]), 
                         fms_a(x.data[1], y.data[1], z.data[1]));
    };
};

//
template<class T>
struct simd_fnma_a<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x, const simd_type& y, const simd_type& z)
    {
        return simd_type(fnma_a(x.data[0], y.data[0], z.data[0]), 
                         fnma_a(x.data[1], y.data[1], z.data[1]));
    };
};

template<class T>
struct simd_fnms_a<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x, const simd_type& y, const simd_type& z)
    {
        return simd_type(fnms_a(x.data[0], y.data[0], z.data[0]), 
                         fnms_a(x.data[1], y.data[1], z.data[1]));
    };
};

template<class T>
struct simd_abs<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x)
    {
        return simd_type(abs(x.data[0]), abs(x.data[1]));
    };
};

template<class T>
struct simd_bitwise_or<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x, const simd_type& y)
    {
        return simd_type(bitwise_or(x.data[0], y.data[0]), 
                         bitwise_or(x.data[1], y.data[1]));
    };
};

template<class T>
struct simd_bitwise_xor<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x, const simd_type& y)
    {
        return simd_type(bitwise_xor(x.data[0], y.data[0]), 
                         bitwise_xor(x.data[1], y.data[1]));
    };
};

template<class T>
struct simd_bitwise_and<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x, const simd_type& y)
    {
        return simd_type(bitwise_and(x.data[0], y.data[0]), 
                         bitwise_and(x.data[1], y.data[1]));
    };
};

template<class T>
struct simd_bitwise_andnot<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x, const simd_type& y)
    {
        return simd_type(bitwise_andnot(x.data[0], y.data[0]), 
                         bitwise_andnot(x.data[1], y.data[1]));
    };
};

template<class T>
struct simd_bitwise_not<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x)
    {
        return simd_type(bitwise_not(x.data[0]), bitwise_not(x.data[1]));
    };
};

template<class T>
struct simd_shift_left<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x, unsigned int y)
    {
        return simd_type(shift_left(x.data[0], y), 
                         shift_left(x.data[1], y));
    };
};

template<class T>
struct simd_shift_right<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x, unsigned int y)
    {
        return simd_type(shift_right(x.data[0], y), 
                         shift_right(x.data[1], y));
    };
};

template<class T>
struct simd_shift_right_arithmetic<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x, unsigned int y)
    {
        return simd_type(shift_right_arithmetic(x.data[0], y), 
                         shift_right_arithmetic(x.data[1], y));
    };
};

template<class T>
struct simd_max<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x, const simd_type& y)
    {
        return simd_type(max(x.data[0], y.data[0]), max(x.data[1], y.data[1]));
    };
};

template<class T>
struct simd_min<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x, const simd_type& y)
    {
        return simd_type(min(x.data[0], y.data[0]), min(x.data[1], y.data[1]));
    };
};

template<class T>
struct simd_sqrt<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x)
    {
        return simd_type(sqrt(x.data[0]), sqrt(x.data[1]));
    };
};

template<class T>
struct simd_round<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x)
    {
        return simd_type(round(x.data[0]), round(x.data[1]));
    };
};

template<class T>
struct simd_floor<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x)
    {
        return simd_type(floor(x.data[0]), floor(x.data[1]));
    };
};

template<class T>
struct simd_ceil<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x)
    {
        return simd_type(ceil(x.data[0]), ceil(x.data[1]));
    };
};

template<class T>
struct simd_trunc<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x)
    {
        return simd_type(trunc(x.data[0]), trunc(x.data[1]));
    };
};

template<class T>
struct simd_eeq<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x, const simd_type& y)
    {
        return simd_type(eeq(x.data[0], y.data[0]), eeq(x.data[1], y.data[1]));
    };
};

template<class T>
struct simd_neq<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x, const simd_type& y)
    {
        return simd_type(neq(x.data[0], y.data[0]), neq(x.data[1], y.data[1]));
    };
};

template<class T>
struct simd_lt<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x, const simd_type& y)
    {
        return simd_type(lt(x.data[0], y.data[0]), lt(x.data[1], y.data[1]));
    };
};

template<class T>
struct simd_gt<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x, const simd_type& y)
    {
        return simd_type(gt(x.data[0], y.data[0]), gt(x.data[1], y.data[1]));
    };
};

template<class T>
struct simd_leq<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x, const simd_type& y)
    {
        return simd_type(leq(x.data[0], y.data[0]), leq(x.data[1], y.data[1]));
    };
};

template<class T>
struct simd_geq<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x, const simd_type& y)
    {
        return simd_type(geq(x.data[0], y.data[0]), geq(x.data[1], y.data[1]));
    };
};

template<class T>
struct simd_any_nan<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static bool eval(const simd_type& x)
    {
        bool b1 = any_nan(x.extract_low());
        bool b2 = any_nan(x.extract_high());

        return b1 || b2;
    };
};

template<class T>
struct simd_is_nan<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x)
    {
        return simd_type(is_nan(x.extract_low()), is_nan(x.extract_high()));
    };
};

template<class T>
struct simd_is_finite<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& x)
    {
        return simd_type(is_finite(x.extract_low()), is_finite(x.extract_high()));
    };
};

template<class T>
struct simd_any<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static bool eval(const simd_type& x)
    {
        bool b1 = any(x.extract_low());
        bool b2 = any(x.extract_high());

        return b1 || b2;
    };
};

template<class T>
struct simd_all<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static bool eval(const simd_type& x)
    {
        bool b1 = all(x.extract_low());
        bool b2 = all(x.extract_high());

        return b1 && b2;
    };
};

//-----------------------------------------------------------------------
//                   CONDITIONAL FUNCTIONS
//-----------------------------------------------------------------------
template<class T>
struct simd_if_then_else<T, 256, sse_tag>
{
    using simd_type = simd<T, 256, sse_tag>;

    force_inline
    static simd_type eval(const simd_type& test, const simd_type& val_true,
                          const simd_type& val_false)
    {
        return simd_type(if_then_else(test.data[0], val_true.data[0], val_false.data[0]),
                         if_then_else(test.data[1], val_true.data[1], val_false.data[1]));
    };
};

}}}
