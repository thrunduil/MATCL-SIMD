/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */


#pragma once

#include "matcl-simd/details/float_binary_rep.h"

namespace matcl { namespace details
{

union convert_int_float
{
    uint32_t    m_int;
    float       m_float;
};

union convert_int_double
{
    uint64_t    m_int;
    double      m_float;
};

}}

namespace matcl
{

force_inline 
float matcl::hex_float(const uint32_t& val)
{
    return reinterpret_cast<const details::convert_int_float*>(&val)->m_float;
};

force_inline double matcl::hex_double(const uint64_t& val)
{
    return reinterpret_cast<const details::convert_int_double*>(&val)->m_float;
};

//-----------------------------------------------------------------------
//                   DOUBLE PRECISION DECODER
//-----------------------------------------------------------------------
force_inline
double_decoder::double_decoder(const double* val)
    :float_value(val)
{};

force_inline
const double& double_decoder::value() const
{ 
    return *float_value;
}

force_inline
const double_binary_rep& double_decoder::get_representation() const
{
    return *ieee_754;
};

force_inline
int double_decoder::get_exponent() const
{ 
    return int(ieee_754->exponent) - double_binary_rep::bias; 
};

force_inline
size_t double_decoder::get_raw_exponent() const
{ 
    return ieee_754->exponent; 
};

force_inline
size_t double_decoder::get_sign() const
{ 
    return ieee_754->sign; 
};

//-----------------------------------------------------------------------
//                   SINGLE PRECISION DECODER
//-----------------------------------------------------------------------
force_inline
float_decoder::float_decoder(const float* val)
    :float_value(val)
{};

force_inline
const float& float_decoder::value() const
{ 
    return *float_value;
}

force_inline
const float_binary_rep& float_decoder::get_representation() const
{
    return *ieee_754;
};

force_inline
int float_decoder::get_exponent() const
{ 
    return int(ieee_754->exponent) - double_binary_rep::bias; 
};

force_inline
size_t float_decoder::get_raw_exponent() const
{ 
    return ieee_754->exponent; 
};

force_inline
size_t float_decoder::get_sign() const
{ 
    return ieee_754->sign; 
};

}
