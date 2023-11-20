/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/config.h"
#include "matcl-simd/details/mpl.h"

namespace matcl { namespace simd
{

namespace md = matcl::details;

// no simd instructions tag
struct nosimd_tag{};

// sse instructions tag
struct sse_tag{};

// avx instructions tag
struct avx_tag{};

// sse instructions tag for vectors containing one value
struct scalar_sse_tag{};

// no simd instructions tag for vectors containing one value
struct scalar_nosimd_tag{};

// simd type storing elements of type Val of total size Bits in bits
// using instruction set determined by Simd_tag
template<class Val, int Bits, class Simd_tag>
class simd
{
    static_assert(md::dependent_false<Val>::value, "unsupported simd type");
};

// simd type storing elements of complex type with real type Val of total size
// Bits in bits, using instruction set determined by Simd_tag
template<class Val, int Bits, class Simd_tag>
class simd_compl
{
    static_assert(md::dependent_false<Val>::value, "unsupported simd_compl type");
};

// number of elements stored in given simd type
template<class Simd_type>
struct vector_size
{
    static const int value = 1;
};

template<class Val, int Bits, class Simd_tag>
struct vector_size<simd<Val, Bits, Simd_tag>>
{
    static const int value = simd<Val, Bits, Simd_tag>::vector_size;
};

template<class Val, int Bits, class Simd_tag>
struct vector_size<simd_compl<Val, Bits, Simd_tag>>
{
    static const int value = simd_compl<Val, Bits, Simd_tag>::vector_size;
};

// is_scalar_tag<Tag>::value is true if Tag is one of the scalar simd tags,
// i.e. scalar_sse_tag or scalar_nosimd_tag
template<class Tag>
struct is_scalar_tag                    { static const bool value = false; };

template<>
struct is_scalar_tag<scalar_sse_tag>    { static const bool value = true; };

template<>
struct is_scalar_tag<scalar_nosimd_tag> { static const bool value = true; };

}}
