/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/config.h"

namespace matcl { namespace simd { namespace details
{

#if MATCL_ARCHITECTURE_HAS_FMA

// return x * y + z; use FMA instruction
inline double fma_f(double x, double y, double z);
inline float  fma_f(float x, float y, float z);

// return x * y - z; use FMA instruction
inline double fms_f(double x, double y, double z);
inline float  fms_f(float x, float y, float z);

// return -x * y + z; use FMA instruction
inline double fnma_f(double x, double y, double z);
inline float  fnma_f(float x, float y, float z);

// return -x * y - z; use FMA instruction
inline double fnms_f(double x, double y, double z);
inline float  fnms_f(float x, float y, float z);

#endif

}}}

#include "matcl-simd/details/func/simd_fma.inl"