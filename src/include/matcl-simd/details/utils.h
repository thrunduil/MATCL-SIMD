/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/config.h"

#include <stdint.h>

namespace matcl { namespace simd { namespace details
{

// integer type of the same sizeof
template<class T> struct integer_type{};
template<>        struct integer_type<float>            { using type = int32_t;};
template<>        struct integer_type<double>           { using type = int64_t;};
template<>        struct integer_type<int32_t>          { using type = int32_t;};
template<>        struct integer_type<int64_t>          { using type = int64_t;};

// unsigned integer type of the same sizeof
template<class T> struct unsigned_integer_type{};
template<>        struct unsigned_integer_type<float>   { using type = uint32_t;};
template<>        struct unsigned_integer_type<double>  { using type = uint64_t;};
template<>        struct unsigned_integer_type<int32_t> { using type = uint32_t;};
template<>        struct unsigned_integer_type<int64_t> { using type = uint64_t;};

}}}
