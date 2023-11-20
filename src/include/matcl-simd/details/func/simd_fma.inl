/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/details/func/simd_fma.h"
#include "matcl-simd/config.h"
#include "matcl-simd/simd_fwd.h"
#include "matcl-simd/simd_general.h"

//#include "matcl-simd/basic_functions.h"
//#include "matcl-simd/other_functions.h"
#include "matcl-simd/details/arch/simd_impl.inl"
//#include "matcl-simd/details/func/simd_func.inl"
//#include "matcl-simd/details/func/other_functions.inl"
#include "matcl-simd/default_simd.h"
//#include "matcl-simd/simd_utils.h"
//#include "matcl-simd/simd.h"

namespace matcl { namespace simd
{

#if MATCL_ARCHITECTURE_HAS_FMA

force_inline
double details::fma_f(double x, double y, double z)
{
    using simd_type = matcl::simd::simd<double,128,sse_tag>;

    simd_type xs(x);
    simd_type ys(y);
    simd_type zs(z);

    simd_type ret   = simd_type(_mm_fmadd_sd( xs.data, ys.data, zs.data));
    return ret.first();
};

force_inline
float details::fma_f(float x, float y, float z)
{
    using simd_type = matcl::simd::simd<float,128,sse_tag>;

    simd_type xs(x);
    simd_type ys(y);
    simd_type zs(z);

    simd_type ret   = simd_type(_mm_fmadd_ss( xs.data, ys.data, zs.data));
    return ret.first();
}

force_inline
double details::fms_f(double x, double y, double z)
{
    using simd_type = matcl::simd::simd<double,128,sse_tag>;

    simd_type xs(x);
    simd_type ys(y);
    simd_type zs(z);

    simd_type ret   = simd_type(_mm_fmsub_sd( xs.data, ys.data, zs.data));
    return ret.first();
}

force_inline
float details::fms_f(float x, float y, float z)
{
    using simd_type = matcl::simd::simd<float,128,sse_tag>;

    simd_type xs(x);
    simd_type ys(y);
    simd_type zs(z);

    simd_type ret   = simd_type(_mm_fmsub_ss( xs.data, ys.data, zs.data));
    return ret.first();
}

force_inline
double details::fnma_f(double x, double y, double z)
{
    using simd_type = matcl::simd::simd<double,128,sse_tag>;

    simd_type xs(x);
    simd_type ys(y);
    simd_type zs(z);

    simd_type ret   = simd_type(_mm_fnmadd_pd( xs.data, ys.data, zs.data));
    return ret.first();
};

force_inline
float details::fnma_f(float x, float y, float z)
{
    using simd_type = matcl::simd::simd<float,128,sse_tag>;

    simd_type xs(x);
    simd_type ys(y);
    simd_type zs(z);

    simd_type ret   = simd_type(_mm_fnmadd_ss( xs.data, ys.data, zs.data));
    return ret.first();
}

force_inline
double details::fnms_f(double x, double y, double z)
{
    using simd_type = matcl::simd::simd<double,128,sse_tag>;

    simd_type xs(x);
    simd_type ys(y);
    simd_type zs(z);

    simd_type ret   = simd_type(_mm_fnmsub_sd( xs.data, ys.data, zs.data));
    return ret.first();
}

force_inline
float details::fnms_f(float x, float y, float z)
{
    using simd_type = matcl::simd::simd<float,128,sse_tag>;

    simd_type xs(x);
    simd_type ys(y);
    simd_type zs(z);

    simd_type ret   = simd_type(_mm_fnmsub_ss( xs.data, ys.data, zs.data));
    return ret.first();
}

#endif

}}