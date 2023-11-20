/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/simd_general.h"
#include "matcl-simd/details/func/simd_func_def.h"

namespace matcl { namespace simd { namespace details
{

template<int Bits, class Simd_tag>
struct simd_signbit_base<float, Bits, Simd_tag>
{
    using simd_type = simd<float, Bits, Simd_tag>;

    force_inline
    static simd_type eval(const simd_type& x)
    {
        return bitwise_and(x, simd_type::minus_zero());
    };
};

template<int Bits, class Simd_tag>
struct simd_signbit_base<double, Bits, Simd_tag>
{
    using simd_type = simd<double, Bits, Simd_tag>;

    force_inline
    static simd_type eval(const simd_type& x)
    {
        return bitwise_and(x, simd_type::minus_zero());
    };
};

//-----------------------------------------------------------------------
//                  simd_reinterpret_as
//-----------------------------------------------------------------------
template<class Val, int Bits, class Tag>
struct simd_reinterpret_as<double, Val, Bits, Tag>
{
    using simd_in   = simd<Val, Bits, Tag>;
    using simd_ret  = simd<double, Bits, Tag>;

    force_inline
    static simd_ret eval(const simd_in& x)
    {
        return x.reinterpret_as_double();
    }
};

template<class Val, int Bits, class Tag>
struct simd_reinterpret_as<float, Val, Bits, Tag>
{
    using simd_in   = simd<Val, Bits, Tag>;
    using simd_ret  = simd<float, Bits, Tag>;

    force_inline
    static simd_ret eval(const simd_in& x)
    {
        return x.reinterpret_as_float();
    }
};

template<class Val, int Bits, class Tag>
struct simd_reinterpret_as<int32_t, Val, Bits, Tag>
{
    using simd_in   = simd<Val, Bits, Tag>;
    using simd_ret  = simd<int32_t, Bits, Tag>;

    force_inline
    static simd_ret eval(const simd_in& x)
    {
        return x.reinterpret_as_int32();
    }
};

template<class Val, int Bits, class Tag>
struct simd_reinterpret_as<int64_t, Val, Bits, Tag>
{
    using simd_in   = simd<Val, Bits, Tag>;
    using simd_ret  = simd<int64_t, Bits, Tag>;

    force_inline
    static simd_ret eval(const simd_in& x)
    {
        return x.reinterpret_as_int64();
    }
};

template<class Val, int Bits, class Tag>
struct simd_reinterpret_as<Val, Val, Bits, Tag>
{
    using simd_in   = simd<Val, Bits, Tag>;
    using simd_ret  = simd<Val, Bits, Tag>;

    force_inline
    static simd_ret eval(const simd_in& x)
    {
        return x;
    }
};

}}}
