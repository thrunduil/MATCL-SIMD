/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/config.h"
#include "matcl-simd/simd_fwd.h"

namespace matcl { namespace details
{

template<class T>
struct is_simd_type
{
    static const bool value = false;
};

template<class T, int Bits, class Tag>
struct is_simd_type<matcl::simd::simd<T, Bits, Tag>>
{
    static const bool value = true;
};

}}
