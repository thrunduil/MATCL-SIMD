/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/config.h"

#include "matcl-simd/details/arch/nosimd/func_complex/simd_compl_func.h"

#if MATCL_ARCHITECTURE_HAS_SSE2
    #include "matcl-simd/details/arch/sse/func_complex/simd_float_128_func.h"
    #include "matcl-simd/details/arch/sse/func_complex/simd_double_128_func.h"
    #include "matcl-simd/details/arch/sse/func_complex/simd_256_func_compl.h"
#endif

#if MATCL_ARCHITECTURE_HAS_AVX
    #include "matcl-simd/details/arch/avx/func_complex/simd_float_256_func.h"
    #include "matcl-simd/details/arch/avx/func_complex/simd_double_256_func.h"
#endif