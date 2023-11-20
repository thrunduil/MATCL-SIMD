/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/math_functions.h"
#include "matcl-simd/details/math/general_defs.h"
#include "matcl-simd/details/math/math_func_impl.inl"
#include "matcl-simd/details/math/math_func_scalar_impl.inl"

#include "matcl-simd/details/arch/nosimd/math/math_impl.h"

#if MATCL_ARCHITECTURE_HAS_SSE2
    #include "matcl-simd/details/arch/sse/math/math_impl.h"
#endif

#if MATCL_ARCHITECTURE_HAS_AVX
    #include "matcl-simd/details/arch/avx/math/math_impl.h"
#endif
