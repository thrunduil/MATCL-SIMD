/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/config.h"
#include "matcl-simd/simd_general.h"
#include "matcl-simd/default_simd.h"

#include <emmintrin.h>

namespace matcl { namespace simd
{

//-------------------------------------------------------------------
//                          SSE2 SCALAR INT64_T
//-------------------------------------------------------------------

// vector of one int64_t scalar
template<>
class alignas(16) simd<int64_t, 128, scalar_sse_tag>
{
    public:
        // implementation type
        using impl_type     = __m128i;

        // type of stored elements
        using value_type    = int64_t;

        // simd tag
        using simd_tag      = scalar_sse_tag;

        // number of bits
        static const int
        number_bits         = 128;

        // type of vector storing half of elements
        using simd_half     = simd<int64_t, 128, scalar_sse_tag>;

        // simd type of the same size storing float values
        using simd_float    = simd<float, 128, scalar_sse_tag>;

        // simd type of the same size storing double values
        using simd_double   = simd<double, 128, scalar_sse_tag>;

        // simd type of the same size storing int32_t values
        using simd_int32    = simd<int32_t, 128, scalar_sse_tag>;

        // simd type of the same size storing int64_t values
        using simd_int64    = simd<int64_t, 128, scalar_sse_tag>;

        // simd type of the same kind storing vector of int64_t integers
        using simd_vector    = simd<int64_t, 128, sse_tag>;

    public:
        // number of elements in the vector
        static const int 
        vector_size         = 1;

    public:
        // internal representation
        impl_type           data;

    public:
        // construct uninitialized vector
        simd() = default;

        // construct vector with all elements equal to val
        explicit simd(int32_t val);

        // construct vector with all elements equal to val
        explicit simd(int64_t val);

        // construct from representation
        simd(const impl_type& v);

        // conversion between simd types
        explicit simd(const simd<int64_t, 128, sse_tag>& s);

        // conversion between simd types
        explicit simd(const simd<int64_t, 128, nosimd_tag>& s);

        // conversion form simd scalar; set all elements to s.first()
        explicit simd(const simd<int64_t, 128, scalar_nosimd_tag>& s);

        // copy constructor
        simd(const simd<int64_t, 128, scalar_sse_tag>& s) = default;

    public:
        // connstruct vector with all elements set to 0
        static simd     zero();

        // connstruct vector with all elements set to 1
        static simd     one();

        // connstruct vector with all elements set to -1
        static simd     minus_one();

    public:
        // construct vector with all elements equal to arr[0]
        static simd     broadcast(const int64_t* arr);

        // construct vector with all elements equal to arr
        static simd     broadcast(const int64_t& arr);

        // construct vector with elements copied from arr; arr must have length
        // at least vector_size
        static simd     load(const int64_t* arr, std::true_type aligned);
        static simd     load(const int64_t* arr, std::false_type not_aligned = std::false_type());

        // gather 64-bit integer elements from memory using 32-bit indices, 
        // i.e. i-th element of resulting vector is arr[ind[i]]
        static simd     gather(const int64_t* arr, const simd_int32& ind);

        // gather 64-bit integer elements from memory using 64-bit indices, 
        // i.e. i-th element of resulting vector is arr[ind[i]]
        static simd     gather(const int64_t* arr, const simd_int64& ind);

        // set the first element in the vector to v and set 0 to all other elements
        static simd     set_lower(int64_t v);

    public:
        // store elements in arr; arr must have length at least vector_size
        void            store(int64_t* arr, std::true_type aligned) const;
        void            store(int64_t* arr, std::false_type not_aligned = std::false_type()) const;

        //store elements with in array with stepping (Step = 1,-1 is not optimized)
        template<int Step>
        void            scatter(int64_t* arr) const;

        // get i-th element from the vector; pos is 0-based
        int64_t         get(int pos) const;

        // return the first element in the vector; equivalent to get(0), but possibly
        // faster
        int64_t         first() const;

        // set i-th element of the vector; pos is 0-based
        void            set(int pos, int64_t val);

        // return pointer to the first element in the vector
        const int64_t*  get_raw_ptr() const;
        int64_t*        get_raw_ptr();

    public:
        // convert elements to int32_t and store the result in the lower part
        simd_int32      convert_to_int32() const;

        // convert elements to double
        simd_double     convert_to_double() const;

        // convert elements to float and store the result in the lower part
        simd_float      convert_to_float() const;

        // reinterpret cast to vector of double of the same kind
        simd_double     reinterpret_as_double() const;

        // reinterpret cast to vector of float of the same kind
        simd_float      reinterpret_as_float() const;

        // reinterpret cast to vector of int32 of the same kind
        simd_int32      reinterpret_as_int32() const;

        // reinterpret cast to simd of the same type storing vectors
        simd_vector     as_vector() const;

    public:
        // plus assign operator
        simd&           operator+=(const simd& x);

        // minus assign operator
        simd&           operator-=(const simd& x);

        // multiply assign operator
        simd&           operator*=(const simd& x);
};

}}
