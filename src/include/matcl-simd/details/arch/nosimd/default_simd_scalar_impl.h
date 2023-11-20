/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/details/arch/simd_impl.h"

namespace matcl { namespace simd
{

template<>
struct default_scalar_simd_type<double>
{ 
    using type = simd<double, 128, scalar_nosimd_tag>; 
};

template<>
struct default_scalar_simd_type<float>
{ 
    using type = simd<float, 128, scalar_nosimd_tag>; 
};

template<>
struct default_scalar_simd_type<int32_t>
{ 
    using type = simd<int32_t, 128, scalar_nosimd_tag>; 
};

template<>
struct default_scalar_simd_type<int64_t>
{ 
    using type = simd<int64_t, 128, scalar_nosimd_tag>; 
};

}}