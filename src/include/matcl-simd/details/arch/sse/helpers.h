/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/simd_general.h"

namespace matcl { namespace simd { namespace details
{

// Generate a constant vector of 4 integers stored in memory,
// load as __m128
template <int I0, int I1, int I2, int I3>
static force_inline __m128i vector_4_int() 
{
    using m128_int4     = union 
                        { 
                            int     i[4];
                            __m128i xmm;
                        };
    
    static const m128_int4 val = {{I0,I1,I2,I3}};
    return val.xmm;
};

}}}
