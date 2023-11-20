/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/config.h"

#if MATCL_USE_MATCL_COMPLEX
    #include "matcl-simd/complex/scalar_types.h"
    #include "matcl-simd/complex/complex_details.h"
#endif

#include "matcl-simd/simd_general.h"

namespace matcl { namespace simd
{

#if MATCL_USE_MATCL_COMPLEX

    using simd_double_complex   = matcl::Complex;
    using simd_single_complex   = matcl::Float_complex;

#else

    //types simd_double_complex and simd_single_complex
    //must already be defined by a user in the namespace matcl::simd

#endif

}}

namespace matcl { namespace simd { namespace details
{

template<class T>   struct real_type                        {};
template<>          struct real_type<simd_single_complex>   { using type = float; };
template<>          struct real_type<simd_double_complex>   { using type = double; };

template<class T, int Bits, class Tag>
                    struct real_type<simd_compl<T,Bits,Tag>>{ using type = simd<T,Bits,Tag>; };

template<class T>   struct complex_type                     {};
template<>          struct complex_type<float>              { using type = simd_single_complex; };
template<>          struct complex_type<double>             { using type = simd_double_complex; };

template<class T, int Bits, class Tag>
                    struct complex_type<simd<T,Bits,Tag>>   { using type = simd_compl<T,Bits,Tag>; };

}}}
