/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/config.h"

#if MATCL_ARCHITECTURE_HAS_SSE2
    #include "matcl-simd/details/arch/sse/default_simd_scalar_impl.h"
#else
    #include "matcl-simd/details/arch/nosimd/default_simd_scalar_impl.h"
#endif
