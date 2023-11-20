/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/math_functions.h"

namespace matcl { namespace simd
{

namespace  ms = matcl::simd;

//-----------------------------------------------------------------------
//                   MATHEMATICAL FUNCTIONS
//-----------------------------------------------------------------------
template<class Val, int Bits, class Simd_tag>
force_inline simd<Val, Bits, Simd_tag> 
ms::pow2k(const simd<Val, Bits, Simd_tag>& k)
{
    return details::simd_pow2k<Val, Bits, Simd_tag>::eval(k);
};

template<int Bits, class Simd_tag>
force_inline simd<float, Bits, Simd_tag> 
ms::pow2ki(const simd<int32_t, Bits, Simd_tag>& k)
{
    return details::simd_pow2k<float, Bits, Simd_tag>::eval_i(k);
};

template<int Bits, class Simd_tag>
force_inline simd<double, Bits, Simd_tag> 
ms::pow2ki(const simd<int64_t, Bits, Simd_tag>& k)
{
    return details::simd_pow2k<double, Bits, Simd_tag>::eval_i(k);
};

template<class Val, int Bits, class Simd_tag>
force_inline simd<Val, Bits, Simd_tag> 
ms::fraction(const simd<Val, Bits, Simd_tag>& x)
{
    return details::simd_fraction<Val, Bits, Simd_tag>::eval(x);
}

template<class Val, int Bits, class Simd_tag>
force_inline simd<typename details::integer_type<Val>::type, Bits, Simd_tag> 
ms::iexponent(const simd<Val, Bits, Simd_tag>& x)
{
    return details::simd_exponent<Val, Bits, Simd_tag>::eval_i(x);
}

template<class Val, int Bits, class Simd_tag>
force_inline simd<Val, Bits, Simd_tag> 
ms::exponent(const simd<Val, Bits, Simd_tag>& x)
{
    return details::simd_exponent<Val, Bits, Simd_tag>::eval(x);
}

template<class Val, int Bits, class Simd_tag>
force_inline simd<Val, Bits, Simd_tag> 
ms::copysign(const simd<Val, Bits, Simd_tag>& x, const simd<Val, Bits, Simd_tag>& y)
{
    return details::simd_copysign<Val, Bits, Simd_tag>::eval(x, y);
}

template<class Val, int Bits, class Simd_tag>
force_inline simd<Val, Bits, Simd_tag> 
ms::exp(const simd<Val, Bits, Simd_tag>& x)
{
    return details::simd_exp<Val, Bits, Simd_tag>::eval(x);
};

template<class Val, int Bits, class Simd_tag>
force_inline simd<Val, Bits, Simd_tag> 
ms::log(const simd<Val, Bits, Simd_tag>& x)
{
    return details::simd_log<Val, Bits, Simd_tag>::eval(x);
};

template<class Val, int Bits, class Simd_tag>
force_inline simd<Val, Bits, Simd_tag> 
ms::sin(const simd<Val, Bits, Simd_tag>& x)
{
    return details::simd_sincos<Val, Bits, Simd_tag>::eval_sin(x);
};

template<class Val, int Bits, class Simd_tag>
force_inline simd<Val, Bits, Simd_tag> 
ms::cos(const simd<Val, Bits, Simd_tag>& x)
{
    return details::simd_sincos<Val, Bits, Simd_tag>::eval_cos(x);
};

template<class Val, int Bits, class Simd_tag>
force_inline void
ms::sincos_simpl(const simd<Val, Bits, Simd_tag>& x, 
    simd<Val, Bits, Simd_tag>& ret_sin, simd<Val, Bits, Simd_tag>& ret_cos)
{
    return details::simd_sincos<Val, Bits, Simd_tag>
                ::eval_sincos_simpl(x, ret_sin, ret_cos);
};

template<class Val, int Bits, class Simd_tag>
force_inline simd<Val, Bits, Simd_tag> 
ms::tan(const simd<Val, Bits, Simd_tag>& x)
{
    return details::simd_tancot<Val, Bits, Simd_tag>::eval_tan(x);
};

template<class Val, int Bits, class Simd_tag>
force_inline simd<Val, Bits, Simd_tag> 
ms::cot(const simd<Val, Bits, Simd_tag>& x)
{
    return details::simd_tancot<Val, Bits, Simd_tag>::eval_cot(x);
};

}}
