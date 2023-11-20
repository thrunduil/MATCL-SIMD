/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

// export macros
#ifdef MATCL_SIMD_EXPORTS
    #define MATCL_SIMD_EXPORT  __declspec(dllexport)
#else
    #define MATCL_SIMD_EXPORT  __declspec(dllimport)
#endif

#ifdef __unix__
    #undef  MATCL_SIMD_EXPORT
    #define MATCL_SIMD_EXPORT
#endif

// portability issues
#ifdef _MSC_VER
    #define force_inline __forceinline
#else
    #define force_inline inline __attribute__((always_inline))
#endif


// define MATCL_USE_MATCL_COMPLEX in order to use
// nondefault complex types; these types must be defined
// before including simd headers

#ifndef MATCL_USE_MATCL_COMPLEX
    #define MATCL_USE_MATCL_COMPLEX 1
#else
    #define MATCL_USE_MATCL_COMPLEX 0
#endif

// enable this macro in order to define functions generating lookup tables
//#define MATCL_SIMD_GENERATE_TABLES

// machine dependent parameters
#include "matcl-simd/machine.h"