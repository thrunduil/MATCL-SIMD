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

// find offset off such that y = (const Type*)ptr + off is aligned to
// Alignment bytes
template<size_t Alignment, class Type>
size_t      get_offset(const void * ptr);

// perform a serializing operation on all store-to-memory instructions that
// were issued prior to this instruction. Guarantees that every store 
// instruction that precedes, in program order, is globally visible before
// any store instruction which follows the fence in program order.
void sfence();

}}

#include "matcl-simd/details/simd_utils.inl"