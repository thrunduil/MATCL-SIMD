/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/config.h"

#include "matcl-simd/details/arch/nosimd/func/simd_func.h"
#include "matcl-simd/details/arch/nosimd/func/simd_128_scalar_func.h"

#if MATCL_ARCHITECTURE_HAS_SSE2
    #include "matcl-simd/details/arch/sse/func/simd_float_128_func.h"
    #include "matcl-simd/details/arch/sse/func/simd_double_128_func.h"
    #include "matcl-simd/details/arch/sse/func/simd_int32_128_func.h"
    #include "matcl-simd/details/arch/sse/func/simd_int64_128_func.h"

    #include "matcl-simd/details/arch/sse/func/simd_256_func.h"
    #include "matcl-simd/details/arch/sse/func/simd_128_scalar_func.h"
#endif

#if MATCL_ARCHITECTURE_HAS_AVX
    #include "matcl-simd/details/arch/avx/func/simd_float_256_func.h"
    #include "matcl-simd/details/arch/avx/func/simd_double_256_func.h"
    #include "matcl-simd/details/arch/avx/func/simd_int32_256_func.h"
    #include "matcl-simd/details/arch/avx/func/simd_int64_256_func.h"
#endif
