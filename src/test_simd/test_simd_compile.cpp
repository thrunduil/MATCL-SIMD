/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#include "test_simd_config.h"
#include "matcl-simd/simd.h"
#include "matcl-simd/simd_complex.h"

namespace matcl { namespace simd
{

template simd<float, 128, nosimd_tag>;
template simd<double, 128, nosimd_tag>;
template simd<int32_t, 128, nosimd_tag>;
template simd<int64_t, 128, nosimd_tag>;

template simd<float, 128, scalar_nosimd_tag>;
template simd<double, 128, scalar_nosimd_tag>;
template simd<int32_t, 128, scalar_nosimd_tag>;
template simd<int64_t, 128, scalar_nosimd_tag>;

template simd_compl<float, 128, nosimd_tag>;
template simd_compl<double, 128, nosimd_tag>;

template simd<float, 256, nosimd_tag>;
template simd<double, 256, nosimd_tag>;
template simd<int32_t, 256, nosimd_tag>;
template simd<int64_t, 256, nosimd_tag>;

template simd_compl<float, 256, nosimd_tag>;
template simd_compl<double, 256, nosimd_tag>;

template void simd<float, 128, nosimd_tag>::scatter<2>(float*) const;
template void simd<double, 128, nosimd_tag>::scatter<2>(double*) const;
template void simd<int32_t, 128, nosimd_tag>::scatter<2>(int32_t*) const;
template void simd<int64_t, 128, nosimd_tag>::scatter<2>(int64_t*) const;

template simd<float, 128, nosimd_tag> simd<float, 128, nosimd_tag>::select<3,2,1,0>() const;
template simd<double, 128, nosimd_tag> simd<double, 128, nosimd_tag>::select<1,1>() const;
template simd<int32_t, 128, nosimd_tag> simd<int32_t, 128, nosimd_tag>::select<3,2,1,0>() const;
template simd<int64_t, 128, nosimd_tag> simd<int64_t, 128, nosimd_tag>::select<1,1>() const;

template void simd<float, 128, scalar_nosimd_tag>::scatter<2>(float*) const;
template void simd<double, 128, scalar_nosimd_tag>::scatter<2>(double*) const;
template void simd<int32_t, 128, scalar_nosimd_tag>::scatter<2>(int32_t*) const;
template void simd<int64_t, 128, scalar_nosimd_tag>::scatter<2>(int64_t*) const;

template void simd<float, 256, nosimd_tag>::scatter<2>(float*) const;
template void simd<double, 256, nosimd_tag>::scatter<2>(double*) const;
template void simd<int32_t, 256, nosimd_tag>::scatter<2>(int32_t*) const;
template void simd<int64_t, 256, nosimd_tag>::scatter<2>(int64_t*) const;

template simd<float, 256, nosimd_tag> simd<float, 256, nosimd_tag>::select<3,2,1,0,0,1,2,3>() const;
template simd<double, 256, nosimd_tag> simd<double, 256, nosimd_tag>::select<3,2,1,0>() const;
template simd<int32_t, 256, nosimd_tag> simd<int32_t, 256, nosimd_tag>::select<3,2,1,0,0,1,2,3>() const;
template simd<int64_t, 256, nosimd_tag> simd<int64_t, 256, nosimd_tag>::select<3,2,1,0>() const;

template void simd_compl<float, 128, nosimd_tag>::scatter<2>(simd_single_complex*) const;
template void simd_compl<double, 128, nosimd_tag>::scatter<2>(simd_double_complex*) const;

template void simd_compl<float, 256, nosimd_tag>::scatter<2>(simd_single_complex*) const;
template void simd_compl<double, 256, nosimd_tag>::scatter<2>(simd_double_complex*) const;


#if MATCL_ARCHITECTURE_HAS_SSE2
    template simd<float, 128, sse_tag>;
    template simd<double, 128, sse_tag>;
    template simd<int32_t, 128, sse_tag>;
    template simd<int64_t, 128, sse_tag>;

    template simd<float, 128, scalar_sse_tag>;
    template simd<double, 128, scalar_sse_tag>;
    template simd<int32_t, 128, scalar_sse_tag>;
    template simd<int64_t, 128, scalar_sse_tag>;

    template simd_compl<float, 128, sse_tag>;
    template simd_compl<double, 128, sse_tag>;

    template simd<float, 256, sse_tag>;
    template simd<double, 256, sse_tag>;
    template simd<int32_t, 256, sse_tag>;
    template simd<int64_t, 256, sse_tag>;

    template simd_compl<float, 256, sse_tag>;
    template simd_compl<double, 256, sse_tag>;

    template void simd<float, 128, sse_tag>::scatter<2>(float*) const;
    template void simd<double, 128, sse_tag>::scatter<2>(double*) const;
    template void simd<int32_t, 128, sse_tag>::scatter<2>(int32_t*) const;
    template void simd<int64_t, 128, sse_tag>::scatter<2>(int64_t*) const;

    template simd<float, 128, sse_tag> simd<float, 128, sse_tag>::select<3,2,1,0>() const;
    template simd<double, 128, sse_tag> simd<double, 128, sse_tag>::select<1,1>() const;
    template simd<int32_t, 128, sse_tag> simd<int32_t, 128, sse_tag>::select<3,2,1,0>() const;
    template simd<int64_t, 128, sse_tag> simd<int64_t, 128, sse_tag>::select<1,1>() const;

    template void simd<float, 128, scalar_sse_tag>::scatter<2>(float*) const;
    template void simd<double, 128, scalar_sse_tag>::scatter<2>(double*) const;
    template void simd<int32_t, 128, scalar_sse_tag>::scatter<2>(int32_t*) const;
    template void simd<int64_t, 128, scalar_sse_tag>::scatter<2>(int64_t*) const;

    template void simd<float, 256, sse_tag>::scatter<2>(float*) const;
    template void simd<double, 256, sse_tag>::scatter<2>(double*) const;
    template void simd<int32_t, 256, sse_tag>::scatter<2>(int32_t*) const;
    template void simd<int64_t, 256, sse_tag>::scatter<2>(int64_t*) const;

    template simd<float, 256, sse_tag> simd<float, 256, sse_tag>::select<3,2,1,0,0,1,2,3>() const;
    template simd<double, 256, sse_tag> simd<double, 256, sse_tag>::select<3,2,1,0>() const;
    template simd<int32_t, 256, sse_tag> simd<int32_t, 256, sse_tag>::select<3,2,1,0,0,1,2,3>() const;
    template simd<int64_t, 256, sse_tag> simd<int64_t, 256, sse_tag>::select<3,2,1,0>() const;

    template void simd_compl<float, 128, sse_tag>::scatter<2>(simd_single_complex*) const;
    template void simd_compl<double, 128, sse_tag>::scatter<2>(simd_double_complex*) const;
    template void simd_compl<float, 256, sse_tag>::scatter<2>(simd_single_complex*) const;
    template void simd_compl<double, 256, sse_tag>::scatter<2>(simd_double_complex*) const;
#endif

#if MATCL_ARCHITECTURE_HAS_AVX
    template simd<float, 256, avx_tag>;
    template simd<double, 256, avx_tag>;
    template simd<int32_t, 256, avx_tag>;
    template simd<int64_t, 256, avx_tag>;

    template simd_compl<float, 256, avx_tag>;
    template simd_compl<double, 256, avx_tag>;

    template void simd<float, 256, avx_tag>::scatter<2>(float*) const;
    template void simd<double, 256, avx_tag>::scatter<2>(double*) const;
    template void simd<int32_t, 256, avx_tag>::scatter<2>(int32_t*) const;
    template void simd<int64_t, 256, avx_tag>::scatter<2>(int64_t*) const;

    template void simd_compl<float, 256, avx_tag>::scatter<2>(simd_single_complex*) const;
    template void simd_compl<double, 256, avx_tag>::scatter<2>(simd_double_complex*) const;

    template simd<float, 256, avx_tag> simd<float, 256, avx_tag>::select<3,2,1,0,0,1,2,3>() const;
    template simd<double, 256, avx_tag> simd<double, 256, avx_tag>::select<3,2,1,0>() const;
    template simd<int32_t, 256, avx_tag> simd<int32_t, 256, avx_tag>::select<3,2,1,0,0,1,2,3>() const;
    template simd<int64_t, 256, avx_tag> simd<int64_t, 256, avx_tag>::select<3,2,1,0>() const;
#endif

}}
