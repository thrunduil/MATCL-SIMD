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

#include <immintrin.h>

namespace matcl { namespace simd
{

//-------------------------------------------------------------------
//                          AVX DOUBLE
//-------------------------------------------------------------------

// vector of four double precision scalars
template<>
class alignas(32) simd<double, 256, avx_tag>
{
    public:
        // implementation type
        using impl_type     = __m256d;

        // type of stored elements
        using value_type    = double;

        // simd tag
        using simd_tag      = avx_tag;

        // number of bits
        static const int
        number_bits         = 256;

        // type of vector storing half of elements
        using simd_half     = simd<double, 128, sse_tag>;

        // simd type of the same size storing float values
        using simd_float    = simd<float, 256, avx_tag>;

        // simd type of the same size storing double values
        using simd_double   = simd<double, 256, avx_tag>;

        // simd type of the same size storing int32_t values
        using simd_int32    = simd<int32_t, 256, avx_tag>;

        // simd type of the same size storing int64_t values
        using simd_int64    = simd<int64_t, 256, avx_tag>;

        // simd type storing half of elements of float type
        using simd_float_half   = simd<float, 128, sse_tag>;

        // simd type storing half of elements of double type
        using simd_double_half  = simd<double, 128, sse_tag>;

        // simd type storing half of elements of int32_t type
        using simd_int32_half   = simd<int32_t, 128, sse_tag>;

        // simd type storing half of elements of int64_t type
        using simd_int64_half   = simd<int64_t, 128, sse_tag>;

    public:
        // number of elements in the vector
        static const int 
        vector_size         = sizeof(impl_type) / sizeof(value_type);    

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

        // construct vector with all elements equal to val
        explicit simd(float val);

        // construct vector with all elements equal to val
        explicit simd(double val);

        // construct vector with first two elements and last two elements
        // copied from lo_hi
        explicit simd(const simd_half& lo_hi);

        // construct vector with i-th element set to vi
        simd(double v0, double v1, double v2, double v3);

        // construct vector with first two elements copied from lo
        // and last two elements copied from hi
        simd(const simd_half& lo, const simd_half& hi);

        // construct from representation
        simd(const impl_type& v);

        // conversion between simd types
        explicit simd(const simd<double, 256, nosimd_tag>& s);
        explicit simd(const simd<double, 256, sse_tag>& s);

        // conversion form simd scalar; set all elements to s.first()
        explicit simd(const simd<double, 128, scalar_sse_tag>& s);
        explicit simd(const simd<double, 128, scalar_nosimd_tag>& s);

        // copy constructor
        simd(const simd<double, 256, avx_tag>& s) = default;

    public:
        // connstruct vector with all elements set to 0.0
        static simd     zero();

        // connstruct vector with all elements set to -0.0
        static simd     minus_zero();

        // connstruct vector with all elements set to 1.0
        static simd     one();

        // connstruct vector with all elements set to -1.0
        static simd     minus_one();

    public:
        // construct vector with all elements equal to arr[0]
        static simd     broadcast(const double* arr);

        // construct vector with all elements equal to arr
        static simd     broadcast(const double& arr);

        // construct vector with elements copied from arr; arr must have length
        // at least vector_size
        static simd     load(const double* arr, std::true_type aligned);
        static simd     load(const double* arr, std::false_type not_aligned = std::false_type());

        // gather double-precision (64-bit) floating-point elements from memory using 
        // 32-bit indices, i.e. i-th element of resulting vector is arr[ind[i]]
        static simd     gather(const double* arr, const simd_int32_half& ind);

        // gather double-precision (64-bit) floating-point elements from memory using 
        // 32-bit indices, i.e. i-th element of resulting vector is arr[ind[i]];
        // only lower part of ind is used
        static simd     gather(const double* arr, const simd_int32& ind);

        // gather double-precision (64-bit) floating-point elements from memory using 
        // 64-bit indices, i.e. i-th element of resulting vector is arr[ind[i]]
        static simd     gather(const double* arr, const simd_int64& ind);

    public:
        // store elements in arr; arr must have length at least vector_size
        void            store(double* arr, std::true_type aligned) const;
        void            store(double* arr, std::false_type not_aligned = std::false_type()) const;

        // store elements in arr using a non-temporal memory hint; arr must have
        // length at least vector_size and must be aligned. After memory transer
        // sfence() might be required in order to synchronize memory with other
        // threads
        void            stream(double* arr, std::true_type aligned) const;

        // store elements with in array with stepping (Step = 1,-1 is not optimized)
        template<int Step>
        void            scatter(double* arr) const;

        // get i-th element from the vector; pos is 0-based
        double          get(int pos) const;

        // return the first element in the vector; equivalent to get(0), 
        // but possibly faster
        double          first() const;

        // set i-th element of the vector; pos is 0-based
        void            set(int pos, double val);

        // return pointer to the first element in the vector
        const double*   get_raw_ptr() const;
        double*         get_raw_ptr();

        // return simd storing first two elements
        simd_half       extract_low() const;

        // return simd storing last two elements
        simd_half       extract_high() const;

        // create a vector with elemens [x[I1], x[I2], x[I3], I[I4]], where x is 
        // this vector, Ik is a 0-based index
        template<int I1, int I2, int I3, int I4>
        simd            select() const;

    public:
        // convert elements to float
        simd_float_half convert_to_float() const;

        // convert elements to int32_t, rounding is performed according
        // to current rounding mode (usually round to nearest ties to even)
        simd_int32_half convert_to_int32() const;

        // convert elements to int32_t, rounding is performed according
        // to current rounding mode (usually round to nearest ties to even)
        simd_int64      convert_to_int64() const;

        // reinterpret cast to vector of floats of the same kind
        simd_float      reinterpret_as_float() const;

        // reinterpret cast to vector of int32 of the same kind
        simd_int32      reinterpret_as_int32() const;

        // reinterpret cast to vector of int64 of the same kind
        simd_int64      reinterpret_as_int64() const;

    public:
        // plus assign operator
        simd&           operator+=(const simd& x);

        // minus assign operator
        simd&           operator-=(const simd& x);

        // multiply assign operator
        simd&           operator*=(const simd& x);

        // divide assign operator
        simd&           operator/=(const simd& x);
};

}}
