/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/details/arch/simd_impl.h"
#include "matcl-simd/complex/simd_complex.h"

namespace matcl { namespace simd
{

template<>
struct default_simd_type<simd_double_complex>
{ 
    using type = simd_compl<double, 256, avx_tag>; 
};

template<>
struct default_simd_type<simd_single_complex>
{ 
    using type = simd_compl<float, 256, avx_tag>; 
};


//
template<>
struct default_simd_bit_size<simd_double_complex, 256>
{
    using type = simd_compl<double, 256, avx_tag>; 
};

template<>
struct default_simd_bit_size<simd_single_complex, 256>
{
    using type = simd_compl<float, 256, avx_tag>; 
};

//
template<>
struct default_simd_bit_size<simd_double_complex, 128>
{
    using type = simd_compl<double, 128, sse_tag>; 
};

template<>
struct default_simd_bit_size<simd_single_complex, 128>
{
    using type = simd_compl<float, 128, sse_tag>; 
};

}}