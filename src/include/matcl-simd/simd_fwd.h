/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/config.h"
//#include "matcl-core/details/mpl.h"

namespace matcl { namespace simd
{

// no simd instructions tag
struct nosimd_tag;

// sse instructions tag
struct sse_tag;

// avx instructions tag
struct avx_tag;

// simd type storing elements of type Val of total size Bits in bits
// using instruction set determined by Simd_tag
template<class Val, int Bits, class Simd_tag>
class simd;

// simd type storing elements of complex type with real type Val of total size
// Bits in bits, using instruction set determined by Simd_tag
template<class Val, int Bits, class Simd_tag>
class simd_compl;

// number of elements stored in given simd type
template<class Simd_type>
struct vector_size;

// simd type for storing values of given type with maximum size
template<class V>
struct default_simd_type;

// simd type for storing values of given type with given register size
// (allowed values for Bits are 128 and 256)
template<class V, int Bits>
struct default_simd_bit_size;

// simd type for storing N values of given type
// (allowed values for N are 1, 2, 4, 8)
template<class V, int N>
struct default_simd_vector_size;

}}

