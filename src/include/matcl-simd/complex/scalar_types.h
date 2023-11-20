/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/config.h"
#include "matcl-simd/complex/complex_type.h"

#include <stdint.h>

namespace matcl
{

template<class T> struct complex;

// signed integer
using Integer       = int;

// single precision floating point number
using Float         = float;

// doule precision floating point number
using Real          = double;

// single precision complex number
using Float_complex = matcl::complex<Float>;

// double precision complex number
using Complex       = matcl::complex<Real>;

// 64-bit signed integer
using Integer_64    = int64_t;

};
