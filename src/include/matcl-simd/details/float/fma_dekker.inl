/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/details/float/fma_dekker.h"

namespace matcl { namespace details
{

// represent z = x * y  as z = xy + err (exactly)
// requires: abs(x) <= 1e995, abs(y) <= 1e995, abs(x*y) <= 1e1021
// ensures: if x*y == 0 || abs(x*y) >= 1e-969, then x*y = xy + err
// modified version of Dekker function (author: Sylvie Boldo, available at
//  http://proval.lri.fr/gallery/Dekker.en.html)
template<class T>
inline
void twofold_mult_dekker_double(const T& x, const T& y, T& xy, T& err)
{
    xy          = x * y;

    double C0   = (double)(0x8000001); //2^27 + 1
    T C         = T(C0);

    T px        = x * C;
    T qx        = x - px;
    T hx        = px + qx;
    T tx        = x - hx;

    T py        = y * C;
    T qy        = y - py;
    T hy        = py + qy;
    T ty        = y - hy;

    err         = (hx * hy) - xy;
    
    err         += hx*ty;
    err         += hy*tx;
    err         += tx*ty;
};

}}

namespace matcl
{

//-----------------------------------------------------------------------
//                   COMPATIBILITY FUNCTIONS
//-----------------------------------------------------------------------
force_inline
void matcl::twofold_mult_dekker(double x, double y, double& xy, double& err)
{
    return details::twofold_mult_dekker_double(x, y, xy, err);
};

force_inline
float matcl::fma_dekker(float x, float y, float z)
{
    //for floats we can use double arithmetics
    double xd   = x;
    double yd   = y;
    double zd   = z;

    // res is exact
    double res  = xd * yd;

    // 0.5 ulp error in double precision
    res         = res + zd;

    // almost 0.5 ulp error in single precision
    return (float)res;
};

}
