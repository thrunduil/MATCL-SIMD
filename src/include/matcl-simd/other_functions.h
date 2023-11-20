/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/simd_general.h"

namespace matcl { namespace simd
{

//-----------------------------------------------------------------------
//                   BIT MANIPULATION
//-----------------------------------------------------------------------

// count the number of leading zero bits in unsigned integer x
uint32_t number_leading_zeros(uint32_t x);
uint64_t number_leading_zeros(uint64_t x);

// count the number of trailing zero bits in unsigned integer x
uint32_t number_trailing_zeros(uint32_t x);
uint64_t number_trailing_zeros(uint64_t x);

// count the number of bits set to 1 in unsigned integer x
uint32_t number_bits_set(uint32_t x);
uint64_t number_bits_set(uint64_t x);

// extract the lowest set bit from unsigned integer x and set the corresponding bit 
// in the result res; all other bits in res are zeroed, and all bits are zeroed if no
// bits are set in x.
uint32_t least_significant_bit(uint32_t x);
uint64_t least_significant_bit(uint64_t x);

//-----------------------------------------------------------------------
//                   ARITHMETIC
//-----------------------------------------------------------------------

// return the high 64 bits of the 128-bit result of the multiplication
uint64_t mulh(uint64_t x, uint64_t y);

}}
