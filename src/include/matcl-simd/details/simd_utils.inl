/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/simd_utils.h"

namespace matcl { namespace simd
{

template<size_t Alignment, class Type>
inline size_t matcl::simd::get_offset(const void * ptr)
{ 
    static const size_t type_sizeof = sizeof(Type);
    static const size_t vec_size    = Alignment / type_sizeof;

    size_t dif  = ((uintptr_t)ptr % Alignment) / type_sizeof; 
    dif         = (vec_size - dif) % vec_size;

    return dif;
}

inline
void matcl::simd::sfence()
{

};

}}
