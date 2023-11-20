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

template<class Val, int Bits, class Simd_tag>
struct simd_compl_reverse{};

template<class Val, int Bits, class Simd_tag>
struct simd_compl_conj{};

template<class Val, int Bits, class Simd_tag>
struct simd_compl_mult{};

template<class Val, int Bits, class Simd_tag>
struct simd_compl_div{};

template<class Val, int Bits, class Simd_tag>
struct simd_compl_plus{};

template<class Val, int Bits, class Simd_tag>
struct simd_compl_minus{};

template<class Val, int Bits, class Simd_tag>
struct simd_compl_uminus{};

template<class Val, int Bits, class Simd_tag>
struct simd_compl_horizontal_sum{};

}}}
