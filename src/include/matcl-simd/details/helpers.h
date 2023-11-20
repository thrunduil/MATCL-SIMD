/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/simd_general.h"

namespace matcl { namespace simd { namespace details
{

template<class Simd_tag>
struct simd_half_tag
{
    using type = Simd_tag;
};

template<>
struct simd_half_tag<avx_tag>
{
    using type = sse_tag;
};


template<class T>
struct simd_compl_from_real{};

template<class T, int Bits, class Tag>
struct simd_compl_from_real<simd<T, Bits, Tag>>
{
    using type = simd_compl<T, Bits, Tag>;
};

}}}
