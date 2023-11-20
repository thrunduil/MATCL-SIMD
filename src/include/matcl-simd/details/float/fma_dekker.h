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

namespace matcl
{

// implementation of fma function using dekker algorithm

// evaluate a * b using the Veltkamp/Dekker algorithm; result is exact; 
// this function is equivalent to twofold_mult and is called by twofold_mult
// and other functions, when FMA instruction is not available
void twofold_mult_dekker(double a, double b, double& val, double& err);

// evaluate x * y + z with one rounding using the Veltkamp/Dekker algorithm
// for double precision arguments and double arithmetics for single precision
// arguments; 
// this function is equivalent to FMA instruction and is called by twofold's
// function, when FMA instruction is not available
float   fma_dekker(float x, float y, float z);

MATCL_SIMD_EXPORT
double  fma_dekker(double x, double y, double z);

// evaluate x * y + z with one rounding using the Veltkamp/Dekker algorithm
// for simd types
#if MATCL_ARCHITECTURE_HAS_SSE2

    simd::simd<float, 128, simd::sse_tag>
    fma_dekker_simd(const simd::simd<float, 128, simd::sse_tag>& x, 
                    const simd::simd<float, 128, simd::sse_tag>& y, 
                    const simd::simd<float, 128, simd::sse_tag>& z);

    MATCL_SIMD_EXPORT
    simd::simd<double, 128, simd::sse_tag>
    fma_dekker_simd(const simd::simd<double, 128, simd::sse_tag>& x, 
                    const simd::simd<double, 128, simd::sse_tag>& y, 
                    const simd::simd<double, 128, simd::sse_tag>& z);
#endif

#if MATCL_ARCHITECTURE_HAS_AVX

    simd::simd<float, 256, simd::avx_tag>
    fma_dekker_simd(const simd::simd<float, 256, simd::avx_tag>& x, 
                    const simd::simd<float, 256, simd::avx_tag>& y, 
                    const simd::simd<float, 256, simd::avx_tag>& z);

    MATCL_SIMD_EXPORT
    simd::simd<double, 256, simd::avx_tag>
    fma_dekker_simd(const simd::simd<double, 256, simd::avx_tag>& x, 
                    const simd::simd<double, 256, simd::avx_tag>& y, 
                    const simd::simd<double, 256, simd::avx_tag>& z);
#endif

}

#include "matcl-simd/details/float/fma_dekker.inl"

