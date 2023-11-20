/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

namespace matcl { namespace simd
{

// simd type for storing values of given type with maximum size
template<class V>
struct default_simd_type 
{
    static_assert(md::dependent_false<V>::value, "unsupported simd type");
};

// simd type for storing one value of given type
template<class V>
struct default_scalar_simd_type
{
    static_assert(md::dependent_false<V>::value, "unsupported simd type");
};

// simd type for storing values of given type with given register size
// (allowed values for Bits are 128 and 256)
template<class V, int Bits>
struct default_simd_bit_size
{
    static_assert(md::dependent_false<V>::value, "unsupported simd type");
};

// simd type for storing N values of given type
// (allowed values for N are 1, 2, 4, 8)
template<class V, int N>
struct default_simd_vector_size
{
    using type = typename default_simd_bit_size<V, N * sizeof(V) * 8>::type;
};

template<class V>
struct default_simd_vector_size<V, 1>
{
    using type = typename default_scalar_simd_type<V>::type;
};

}}

// specialize default_simd_type type for given type and given architecture
#include "matcl-simd/details/arch/default_simd.h"
#include "matcl-simd/details/arch/default_simd_scalar.h"

