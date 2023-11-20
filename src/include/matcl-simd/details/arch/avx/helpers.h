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

// Generate a constant vector of 8 integers stored in memory,
// load as __m256
template <int I0, int I1, int I2, int I3, int I4, int I5, int I6, int I7>
static force_inline __m256i vector_8_int() 
{
    using m256_int8     = union 
                        { 
                            int     i[8];
                            __m256i ymm;
                        };
    
    static const m256_int8 val = {{I0,I1,I2,I3,I4,I5,I6,I7}};
    return val.ymm;
};

}}}
