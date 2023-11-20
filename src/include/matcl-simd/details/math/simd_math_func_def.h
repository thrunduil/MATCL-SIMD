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

namespace ms = matcl::simd;

template<class Val, int Bits, class Simd_tag>
struct simd_exp
{
    static_assert(md::dependent_false<Simd_tag>::value, 
                "function exp not defined for for given arguments");
};

template<class Val, int Bits, class Simd_tag>
struct simd_log
{
    static_assert(md::dependent_false<Simd_tag>::value, 
                "function log not defined for for given arguments");
};

template<class Val, int Bits, class Simd_tag>
struct simd_sincos
{
    static_assert(md::dependent_false<Simd_tag>::value, 
                "function sin/cos not defined for for given arguments");
};

template<class Val, int Bits, class Simd_tag>
struct simd_tancot
{
    static_assert(md::dependent_false<Simd_tag>::value, 
                "function tan/cot not defined for for given arguments");
};

template<class Val, int Bits, class Simd_tag>
struct simd_pow2k
{
    static_assert(md::dependent_false<Simd_tag>::value, 
                "function pow2k not defined for for given arguments");
};

template<class Val, int Bits, class Simd_tag>
struct simd_exponent
{
    static_assert(md::dependent_false<Simd_tag>::value, 
                "function exponent not defined for for given arguments");
};

template<class Val, int Bits, class Simd_tag>
struct simd_fraction
{
    static_assert(md::dependent_false<Simd_tag>::value, 
                "function fraction not defined for for given arguments");
};

template<class Val, int Bits, class Simd_tag>
struct simd_copysign
{
    static_assert(md::dependent_false<Simd_tag>::value, 
                "function copysign not defined for for given arguments");
};

}}}
