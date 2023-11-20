/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/config.h"

#if MATCL_ARCHITECTURE_HAS_AVX
    #include "matcl-simd/details/arch/avx/default_simd_impl.h"
#elif MATCL_ARCHITECTURE_HAS_SSE2
    #include "matcl-simd/details/arch/sse/default_simd_impl.h"
#else
    #include "matcl-simd/details/arch/nosimd/default_simd_impl.h"
#endif
