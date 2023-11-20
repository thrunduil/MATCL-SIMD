/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/config.h"

#include "matcl-simd/arch/nosimd/simd_float_128.h"
#include "matcl-simd/arch/nosimd/simd_double_128.h"
#include "matcl-simd/arch/nosimd/simd_int32_128.h"
#include "matcl-simd/arch/nosimd/simd_int64_128.h"

#include "matcl-simd/arch/nosimd/simd_scalar_float_128.h"
#include "matcl-simd/arch/nosimd/simd_scalar_double_128.h"
#include "matcl-simd/arch/nosimd/simd_scalar_int32_128.h"
#include "matcl-simd/arch/nosimd/simd_scalar_int64_128.h"

#include "matcl-simd/arch/nosimd/simd_float_256.h"
#include "matcl-simd/arch/nosimd/simd_double_256.h"
#include "matcl-simd/arch/nosimd/simd_int32_256.h"
#include "matcl-simd/arch/nosimd/simd_int64_256.h"

#if MATCL_ARCHITECTURE_HAS_SSE2
    #include "matcl-simd/arch/sse/simd_double_128.h"
    #include "matcl-simd/arch/sse/simd_float_128.h"
    #include "matcl-simd/arch/sse/simd_int32_128.h"
    #include "matcl-simd/arch/sse/simd_int64_128.h"
    
    #include "matcl-simd/arch/sse/simd_double_256.h"
    #include "matcl-simd/arch/sse/simd_float_256.h"
    #include "matcl-simd/arch/sse/simd_int32_256.h"
    #include "matcl-simd/arch/sse/simd_int64_256.h"

    #include "matcl-simd/arch/sse/simd_scalar_double_128.h"
    #include "matcl-simd/arch/sse/simd_scalar_float_128.h"
    #include "matcl-simd/arch/sse/simd_scalar_int32_128.h"
    #include "matcl-simd/arch/sse/simd_scalar_int64_128.h"
#endif

#if MATCL_ARCHITECTURE_HAS_AVX
    #include "matcl-simd/arch/avx/simd_double_256.h"
    #include "matcl-simd/arch/avx/simd_float_256.h"
    #include "matcl-simd/arch/avx/simd_int32_256.h"
    #include "matcl-simd/arch/avx/simd_int64_256.h"
#endif