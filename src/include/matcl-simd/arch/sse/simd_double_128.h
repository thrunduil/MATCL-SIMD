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
//                          SSE2 DOUBLE
//-------------------------------------------------------------------

// vector of two double precision scalars
template<>
class alignas(16) simd<double, 128, sse_tag>
{
    public:
        // implementation type
        using impl_type     = __m128d;

        // type of stored elements
        using value_type    = double;

        // simd tag
        using simd_tag      = sse_tag;

        // number of bits
        static const int
        number_bits         = 128;

        // type of vector storing half of elements
        using simd_half     = simd<double, 128, sse_tag>;

        // simd type of the same size storing float values
        using simd_float    = simd<float, 128, sse_tag>;

        // simd type of the same size storing double values
        using simd_double   = simd<double, 128, sse_tag>;

        // simd type of the same size storing int32_t values
        using simd_int32    = simd<int32_t, 128, sse_tag>;

        // simd type of the same size storing int64_t values
        using simd_int64    = simd<int64_t, 128, sse_tag>;

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

        // set the first element in the vector to v1 and the second element to v2
        simd(double v1, double v2);

        // construct vector with first element copied from lo
        // and last element copied from hi; only lower part of lo and hi is used
        simd(const simd& lo, const simd& hi);

        // construct from representation
        simd(const impl_type& v);

        // conversion between simd types
        explicit simd(const simd<double, 128, nosimd_tag>& s);        

        // conversion form simd scalar; set all elements to s.first()
        explicit simd(const simd<double, 128, scalar_sse_tag>& s);
        explicit simd(const simd<double, 128, scalar_nosimd_tag>& s);

        // copy constructor
        simd(const simd<double, 128, sse_tag>& s) = default;

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
        static simd     gather(const double* arr, const simd_int32& ind);

        // gather double-precision (64-bit) floating-point elements from memory using 
        // 64-bit indices, i.e. i-th element of resulting vector is arr[ind[i]]
        static simd     gather(const double* arr, const simd_int64& ind);

        // set the first element in the vector to v and set 0 to all other elements
        static simd     set_lower(double v);

    public:
        // store elements in arr; arr must have length at least vector_size
        void            store(double* arr, std::true_type aligned) const;
        void            store(double* arr, std::false_type not_aligned = std::false_type()) const;

        //store elements with in array with stepping (Step = 1,-1 is not optimized)
        template<int Step>
        void            scatter(double* arr) const;

        // get i-th element from the vector; pos is 0-based
        double          get(int pos) const;

        // return the first element in the vector; equivalent to get(0), but possibly
        // faster
        double          first() const;

        // set i-th element of the vector; pos is 0-based
        void            set(int pos, double val);

        // return pointer to the first element in the vector
        const double*   get_raw_ptr() const;
        double*         get_raw_ptr();

        // return simd storing first element
        simd            extract_low() const;

        // return simd storing last element
        simd            extract_high() const;

        // create a vector with elemens [x[I1], x[I2]], where x is this vector, 
        // Ik is a 0-based index
        template<int I1, int I2>
        simd            select() const;

        // create a vector with elements [z[I1], z[I2]], where z = [x, y] is the
        // concatenated vector of x and y, Ik is a 0-based index
        template<int I1, int I2>
        static simd     combine(const simd& x, const simd& y);

    public:
        // convert elements to float and store the result in the lower part
        simd_float      convert_to_float() const;

        // convert elements to int32_t, rounding is performed according
        // to current rounding mode (usually round to nearest ties to even)
        simd_int32      convert_to_int32() const;

        // convert elements to int64_t, rounding is performed according
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
