/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/basic_complex_functions.h"
#include "matcl-simd/details/func/simd_func_complex_def.h"
#include "matcl-simd/details/arch/simd_func_complex_impl.h"

namespace matcl { namespace simd
{

namespace ms = matcl::simd;

template<class Val, int Bits, class Simd_tag>
force_inline
simd_compl<Val, Bits, Simd_tag> 
ms::reverse(const simd_compl<Val, Bits, Simd_tag>& x)
{
    return details::simd_compl_reverse<Val, Bits, Simd_tag>::eval(x);
};

template<class Val, int Bits, class Simd_tag>
force_inline
simd_compl<Val, Bits, Simd_tag> 
ms::conj(const simd_compl<Val, Bits, Simd_tag>& x)
{
    return details::simd_compl_conj<Val, Bits, Simd_tag>::eval(x);
};

template<class Val, int Bits, class Simd_tag>
force_inline
simd_compl<Val, Bits, Simd_tag> 
ms::operator*(const simd_compl<Val, Bits, Simd_tag>& x, const simd_compl<Val, Bits, Simd_tag>& y)
{
    return details::simd_compl_mult<Val, Bits, Simd_tag>::eval(x, y);
};

template<class Val, int Bits, class Simd_tag>
force_inline
simd_compl<Val, Bits, Simd_tag>
ms::operator*(const simd<Val, Bits, Simd_tag>& x, const simd_compl<Val, Bits, Simd_tag>& y)
{
    return details::simd_compl_mult<Val, Bits, Simd_tag>::eval_rc(x, y);
};

template<class Val, int Bits, class Simd_tag>
force_inline
simd_compl<Val, Bits, Simd_tag>
ms::operator*(const simd_compl<Val, Bits, Simd_tag>& x, const simd<Val, Bits, Simd_tag>& y)
{
    return details::simd_compl_mult<Val, Bits, Simd_tag>::eval_cr(x, y);
};

template<class Val, int Bits, class Simd_tag>
force_inline
simd_compl<Val, Bits, Simd_tag> 
ms::operator/(const simd_compl<Val, Bits, Simd_tag>& x, const simd_compl<Val, Bits, Simd_tag>& y)
{
    return details::simd_compl_div<Val, Bits, Simd_tag>::eval(x, y);
};

template<class Val, int Bits, class Simd_tag>
force_inline
simd_compl<Val, Bits, Simd_tag>
ms::operator/(const simd<Val, Bits, Simd_tag>& x, const simd_compl<Val, Bits, Simd_tag>& y)
{
    return details::simd_compl_div<Val, Bits, Simd_tag>::eval_rc(x, y);
};

template<class Val, int Bits, class Simd_tag>
force_inline
simd_compl<Val, Bits, Simd_tag>
ms::operator/(const simd_compl<Val, Bits, Simd_tag>& x, const simd<Val, Bits, Simd_tag>& y)
{
    return details::simd_compl_div<Val, Bits, Simd_tag>::eval_cr(x, y);
};

template<class Val, int Bits, class Simd_tag>
force_inline
simd_compl<Val, Bits, Simd_tag>
ms::operator+(const simd_compl<Val, Bits, Simd_tag>& x, const simd_compl<Val, Bits, Simd_tag>& y)
{
    return details::simd_compl_plus<Val, Bits, Simd_tag>::eval(x, y);
};

template<class Val, int Bits, class Simd_tag>
force_inline
simd_compl<Val, Bits, Simd_tag>
ms::operator-(const simd_compl<Val, Bits, Simd_tag>& x, const simd_compl<Val, Bits, Simd_tag>& y)
{
    return details::simd_compl_minus<Val, Bits, Simd_tag>::eval(x, y);
};

template<class Val, int Bits, class Simd_tag>
force_inline
simd_compl<Val, Bits, Simd_tag> 
ms::operator-(const simd_compl<Val, Bits, Simd_tag>& x)
{
    return details::simd_compl_uminus<Val, Bits, Simd_tag>::eval(x);
};

template<class Val, int Bits, class Simd_tag>
force_inline
typename simd_compl<Val, Bits, Simd_tag>::value_type
ms::horizontal_sum(const simd_compl<Val, Bits, Simd_tag>& x)
{
    return details::simd_compl_horizontal_sum<Val, Bits, Simd_tag>::eval(x);
};

template<class Val, int Bits, class Simd_tag>
std::ostream& ms::operator<<(std::ostream& os, const simd_compl<Val, Bits, Simd_tag>& x)
{
    int vec_size    = simd_compl<Val, Bits, Simd_tag>::vector_size;
    const Val* ptr  = x.get_raw_ptr();

    os << "{" << ptr[0];

    for (int i = 1; i < vec_size; ++i)
        os << ", " << ptr[i];

    os << "}";

    return os;
};

// return true if at least element in the vector x is NAN
template<class Val, int Bits, class Simd_tag>
force_inline bool
any_nan(const simd_compl<Val, Bits, Simd_tag>& x)
{
    return any_nan(x.data);
}

}}
