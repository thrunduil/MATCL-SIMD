/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/details/float/fma_dekker.h"
#include "matcl-simd/simd.h"

namespace matcl
{

//-----------------------------------------------------------------------
//                   COMPATIBILITY FUNCTIONS
//-----------------------------------------------------------------------

#if MATCL_ARCHITECTURE_HAS_SSE2

force_inline
simd::simd<float, 128, simd::sse_tag>
matcl::fma_dekker_simd(const simd::simd<float, 128, simd::sse_tag>& x, 
                const simd::simd<float, 128, simd::sse_tag>& y, 
                const simd::simd<float, 128, simd::sse_tag>& z)
{
    using simd_float    = simd::simd<float, 128, simd::sse_tag>;
    using simd_double   = simd_float::simd_double_2;

    //for floats we can use double arithmetics
    simd_double xd      = x.convert_to_double();
    simd_double yd      = y.convert_to_double();
    simd_double zd      = z.convert_to_double();

    // res is exact
    simd_double res     = xd * yd;

    // 0.5 ulp error in double precision
    res                 = res + zd;

    // almost 0.5 ulp error in single precision
    simd_float resf     = res.convert_to_float();
    return resf;
}

#endif

#if MATCL_ARCHITECTURE_HAS_AVX

force_inline
simd::simd<float, 256, simd::avx_tag>
matcl::fma_dekker_simd(const simd::simd<float, 256, simd::avx_tag>& x, 
                const simd::simd<float, 256, simd::avx_tag>& y, 
                const simd::simd<float, 256, simd::avx_tag>& z)
{
    using simd_float    = simd::simd<float, 256, simd::avx_tag>;
    using simd_double   = simd::simd<double, 256, simd::avx_tag>;
    using simd_half     = simd_float::simd_half;

    //for floats we can use double arithmetics
    simd_double xd_l    = x.convert_low_to_double();
    simd_double xd_h    = x.convert_high_to_double();
    simd_double yd_l    = y.convert_low_to_double();
    simd_double yd_h    = y.convert_high_to_double();
    simd_double zd_l    = z.convert_low_to_double();
    simd_double zd_h    = z.convert_high_to_double();

    // res is exact
    simd_double res_l   = xd_l * yd_l;
    simd_double res_h   = xd_h * yd_h;

    // 0.5 ulp error in double precision
    res_l               = res_l + zd_l;
    res_h               = res_h + zd_h;

    // almost 0.5 ulp error in single precision
    simd_half resf_l    = res_l.convert_to_float();
    simd_half resf_h    = res_h.convert_to_float();
    
    return simd_float(resf_l, resf_h);
};

#endif

}