/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/config.h"
#include "matcl-simd/complex/scalar_types.h"
#include "matcl-simd/details/float/fma_dekker.h"

#if MATCL_ARCHITECTURE_HAS_FMA
    #include "matcl-simd/details/func/simd_fma.h"
#endif

#include <cfloat>
#include <fenv.h> 
#include <limits>

namespace matcl { namespace constants
{

// infinite value
template<class Value>
Value   inf();

template<> inline
Float   inf<>()              { return std::numeric_limits< Float >::infinity();};

template<> inline 
Real    inf<>()              { return std::numeric_limits< Real >::infinity();};

}}

namespace matcl { namespace raw { namespace details
{

namespace scal_func
{
    namespace mrd = matcl::raw::details;

    //--------------------------------------------------------------------
    force_inline bool finite(double x)
    {
        return x-x == 0;
        //std::isfinite is incredibly slow (dll function call)
        //return (std::isfinite(x)) ? 1 : 0;
    };
    force_inline bool finite(float x)
    {
        return x-x == 0;
        //std::isfinite is incredibly slow (dll function call)
        //return (std::isfinite(x)) ? 1 : 0;
    };

    //--------------------------------------------------------------------
    force_inline bool isnan(Integer)
    {
        return false;
    };
    force_inline bool isnan(double x)
    {
        return x != x;
        //return (std::isnan(x)) ? 1 : 0;
    };
    force_inline bool isnan(float x)
    {
        return x != x;
        //return (std::isnan(x)) ? 1 : 0;
    };

    //--------------------------------------------------------------------
    force_inline double abs(double x) 
    { 
        return std::abs(x);
    };
    force_inline float abs(float x) 
    { 
        return std::abs(x);
    };
    force_inline Integer abs(Integer x) 
    { 
        return x < 0 ? - x : x; 
    };

    //--------------------------------------------------------------------
    force_inline bool isinf(double x)
    {
        return (scal_func::isnan(x) || scal_func::finite(x)) ? 0 : 1;
    };
    force_inline bool isinf(float x)
    {
        return (scal_func::isnan(x) || scal_func::finite(x)) ? 0 : 1;
    };

    //--------------------------------------------------------------------
    force_inline double copysign(double x, double y)
    {
        return std::copysign(x,y);
    }
    force_inline double copysign(double x, float y)
    {
        return std::copysign(x,y);
    }
    force_inline float copysign(float x, float y)
    {
        return std::copysign(x,y);
    }
    force_inline double copysign(float x, double y)
    {
        return std::copysign(x,y);
    }

    //--------------------------------------------------------------------
    force_inline double fma_f(double x, double y, double z)
    {
        #if MATCL_ARCHITECTURE_HAS_FMA
            return simd::details::fma_f(x, y, z);
        #else
            return x * y + z;
        #endif
    };

    force_inline float fma_f(float x, float y, float z)
    {
        #if MATCL_ARCHITECTURE_HAS_FMA
            return simd::details::fma_f(x, y, z);
        #else
            return x * y + z;
        #endif
    };

    //--------------------------------------------------------------------
    force_inline double fms_f(double x, double y, double z)
    {
        #if MATCL_ARCHITECTURE_HAS_FMA
            return simd::details::fms_f(x, y, z);
        #else
            return x * y - z;
        #endif
    };
    force_inline float fms_f(float x, float y, float z)
    {
        #if MATCL_ARCHITECTURE_HAS_FMA
            return simd::details::fms_f(x, y, z);
        #else
            return x * y - z;
        #endif
    };

    //--------------------------------------------------------------------
    force_inline double fnma_f(double x, double y, double z)
    {
        #if MATCL_ARCHITECTURE_HAS_FMA
            return simd::details::fnma_f(x, y, z);
        #else
            return z - x * y;
        #endif
    };

    force_inline float fnma_f(float x, float y, float z)
    {
        #if MATCL_ARCHITECTURE_HAS_FMA
            return simd::details::fnma_f(x, y, z);
        #else
            return z - x * y;
        #endif
    };

    //--------------------------------------------------------------------
    force_inline double fnms_f(double x, double y, double z)
    {
        #if MATCL_ARCHITECTURE_HAS_FMA
            return simd::details::fnms_f(x, y, z);
        #else
            return -(x * y + z);
        #endif
    };
    force_inline float fnms_f(float x, float y, float z)
    {
        #if MATCL_ARCHITECTURE_HAS_FMA
            return simd::details::fnms_f(x, y, z);
        #else
            return -(x * y + z);
        #endif
    };

    //--------------------------------------------------------------------
    force_inline double fma_a(double x, double y, double z)
    {
        // do not use std::fma, this function is incredibly slow on VS

        #if MATCL_ARCHITECTURE_HAS_FMA
            return simd::details::fma_f(x, y, z);
        #else
            return fma_dekker(x, y, z);
        #endif
    };

    force_inline float fma_a(float x, float y, float z)
    {
        // do not use std::fma, this function is incredibly slow on VS

        #if MATCL_ARCHITECTURE_HAS_FMA
            return simd::details::fma_f(x, y, z);
        #else
            return fma_dekker(x, y, z);
        #endif
    };

    //--------------------------------------------------------------------
    force_inline double fms_a(double x, double y, double z)
    {
        // do not use std::fma, this function is incredibly slow on VS

        #if MATCL_ARCHITECTURE_HAS_FMA
            return simd::details::fms_f(x, y, z);
        #else
            return fma_dekker(x, y, -z);
        #endif
    };
    force_inline float fms_a(float x, float y, float z)
    {
        // do not use std::fma, this function is incredibly slow on VS

        #if MATCL_ARCHITECTURE_HAS_FMA
            return simd::details::fms_f(x, y, z);
        #else
            return fma_dekker(x, y, -z);
        #endif
    };

    //--------------------------------------------------------------------
    force_inline double fnma_a(double x, double y, double z)
    {
        // do not use std::fma, this function is incredibly slow on VS

        #if MATCL_ARCHITECTURE_HAS_FMA
            return simd::details::fnma_f(x, y, z);
        #else
            return fma_dekker(-x, y, z);
        #endif
    };

    force_inline float fnma_a(float x, float y, float z)
    {
        // do not use std::fma, this function is incredibly slow on VS

        #if MATCL_ARCHITECTURE_HAS_FMA
            return simd::details::fnma_f(x, y, z);
        #else
            return fma_dekker(-x, y, z);
        #endif
    };

    //--------------------------------------------------------------------
    force_inline double fnms_a(double x, double y, double z)
    {
        // do not use std::fma, this function is incredibly slow on VS

        #if MATCL_ARCHITECTURE_HAS_FMA
            return simd::details::fnms_f(x, y, z);
        #else
            return -fma_dekker(x, y, z);
        #endif
    };
    force_inline float fnms_a(float x, float y, float z)
    {
        // do not use std::fma, this function is incredibly slow on VS

        #if MATCL_ARCHITECTURE_HAS_FMA
            return simd::details::fnms_f(x, y, z);
        #else
            return -fma_dekker(x, y, z);
        #endif
    };
}

}}}
