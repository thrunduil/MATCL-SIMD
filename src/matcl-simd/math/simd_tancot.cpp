/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/details/math/impl/simd_tan_double.h"
#include "matcl-simd/details/math/impl/simd_tan_float.h"

namespace matcl { namespace simd { namespace details
{

//-----------------------------------------------------------------------
//                              DOUBLE
//-----------------------------------------------------------------------

const double simd_tancot_table_double_data::poly_tan_nom[] = 
{
     -1.666666666666666664854175324915915e-01,
    2.107208398174823060978142796523415e-01,
    -1.203504503424041124654801276389759e-02,
    1.279768844094433393003265898653200e-04,
};

const double simd_tancot_table_double_data::poly_tan_den[] = 
{
     1.000000000000000000000000000000000e+00,
    -4.643250389048939857084143787639371e-01,
    2.455976289105447338765279443560907e-02,
    -2.559895173431206769380319886187810e-04,
};

const double simd_tancot_table_double_data::poly_tan_nomden[] = 
{
     -1.666666666666666664854175324915915e-01,  1.000000000000000000000000000000000e+00,
    2.107208398174823060978142796523415e-01,   -4.643250389048939857084143787639371e-01,
    -1.203504503424041124654801276389759e-02,  2.455976289105447338765279443560907e-02,
    1.279768844094433393003265898653200e-04,   -2.559895173431206769380319886187810e-04,
};

//-----------------------------------------------------------------------
//                              FOAT
//-----------------------------------------------------------------------

const float simd_tancot_table_float_data::poly_tan[] = 
{
    -1.666666556272070866664759571415666e-01f,
    1.333317681091376226379620308908976e-01f,
    5.400479260564452490896424503784493e-02f,
    2.154925243305569542319363009012898e-02f,
    1.018787024491881392714498202280144e-02f,
    8.589519476173179085520507066543503e-04f,
    4.019965276430945044709486312112068e-03f,
};

const double simd_tancot_table_float_data::poly_tan_double[] = 
{
    -1.666666556272070866664759571415666e-01,
    1.333317681091376226379620308908976e-01,
    5.400479260564452490896424503784493e-02,
    2.154925243305569542319363009012898e-02,
    1.018787024491881392714498202280144e-02,
    8.589519476173179085520507066543503e-04,
    4.019965276430945044709486312112068e-03,
};

}}}
