/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/details/arch/simd_impl.h"
#include "matcl-simd/details/math/simd_math_func_def.h"
#include "matcl-simd/details/scalar_mat_func.h"

namespace matcl { namespace simd { namespace details
{

//-----------------------------------------------------------------------
//                          exp
//-----------------------------------------------------------------------
template<int Bits>
struct simd_exp<double, Bits, nosimd_tag>
{
    using simd_type     = simd<double, Bits, nosimd_tag>;

    force_inline
    static simd_type eval(const simd_type& a)
    {
        static const 
        int vec_size    = simd_type::vector_size;

        simd_type res;

        const double* ptr_a = a.get_raw_ptr();
        double* ptr_res     = res.get_raw_ptr();

        for (int i = 0; i < vec_size; ++i)
            ptr_res[i]      = ms::exp(ptr_a[i]);

        return res;
    };
};

template<int Bits>
struct simd_exp<float, Bits, nosimd_tag>
{
    using simd_type     = simd<float, Bits, nosimd_tag>;

    force_inline
    static simd_type eval(const simd_type& a)
    {
        static const 
        int vec_size    = simd_type::vector_size;

        simd_type res;

        const float* ptr_a  = a.get_raw_ptr();
        float* ptr_res      = res.get_raw_ptr();

        for (int i = 0; i < vec_size; ++i)
            ptr_res[i]      = ms::exp(ptr_a[i]);

        return res;
    };
};

//-----------------------------------------------------------------------
//                          log
//-----------------------------------------------------------------------
template<int Bits>
struct simd_log<double, Bits, nosimd_tag>
{
    using simd_type     = simd<double, Bits, nosimd_tag>;

    force_inline
    static simd_type eval(const simd_type& a)
    {
        static const 
        int vec_size    = simd_type::vector_size;

        simd_type res;

        const double* ptr_a = a.get_raw_ptr();
        double* ptr_res     = res.get_raw_ptr();

        for (int i = 0; i < vec_size; ++i)
            ptr_res[i]      = ms::log(ptr_a[i]);

        return res;
    };
};

template<int Bits>
struct simd_log<float, Bits, nosimd_tag>
{
    using simd_type     = simd<float, Bits, nosimd_tag>;

    force_inline
    static simd_type eval(const simd_type& a)
    {
        static const 
        int vec_size    = simd_type::vector_size;

        simd_type res;

        const float* ptr_a  = a.get_raw_ptr();
        float* ptr_res      = res.get_raw_ptr();

        for (int i = 0; i < vec_size; ++i)
            ptr_res[i]      = ms::log(ptr_a[i]);

        return res;
    };
};

//-----------------------------------------------------------------------
//                          pow2k
//-----------------------------------------------------------------------
template<class T, int Bits>
struct simd_pow2k<T, Bits, nosimd_tag>
{
    using simd_type = simd<T, Bits, nosimd_tag>;
    using int_type  = typename details::integer_type<T>::type;
    using simd_int  = simd<int_type, Bits, nosimd_tag>;

    static const int 
    vector_size     = simd_type::vector_size;

    force_inline
    static simd_type eval(const simd_type& k)
    {
        simd_type res;

        for (int i = 0; i < vector_size; ++i)
            res.data[i] = matcl::simd::scalar_func::pow2k(k.data[i]);

        return res;
    };

    force_inline
    static simd_type eval_i(const simd_int& k)
    {
        simd_type res;

        for (int i = 0; i < vector_size; ++i)
            res.data[i] = matcl::simd::scalar_func::pow2ki(k.data[i]);

        return res;
    };
};

template<class T, int Bits>
struct simd_pow2k<T, Bits, scalar_nosimd_tag>
{
    using simd_type = simd<T, Bits, scalar_nosimd_tag>;
    using int_type  = typename details::integer_type<T>::type;
    using simd_int  = simd<int_type, Bits, scalar_nosimd_tag>;

    force_inline
    static simd_type eval(const simd_type& k)
    {
        return simd_type(matcl::simd::scalar_func::pow2k(k.data));
    };

    force_inline
    static simd_type eval_i(const simd_int& k)
    {
        return simd_type(matcl::simd::scalar_func::pow2ki(k.data));
    };
};

//-----------------------------------------------------------------------
//                          fraction
//-----------------------------------------------------------------------
template<class T, int Bits>
struct simd_fraction<T, Bits, nosimd_tag>
{
    using simd_type = simd<T, Bits, nosimd_tag>;
    using int_type  = typename details::integer_type<T>::type;
    using simd_int  = simd<int_type, Bits, nosimd_tag>;

    static const int 
    vector_size     = simd_type::vector_size;

    force_inline
    static simd_type eval(const simd_type& k)
    {
        simd_type res;

        for (int i = 0; i < vector_size; ++i)
            res.data[i] = matcl::simd::scalar_func::fraction(k.data[i]);

        return res;
    };
};

template<class T, int Bits>
struct simd_fraction<T, Bits, scalar_nosimd_tag>
{
    using simd_type = simd<T, Bits, scalar_nosimd_tag>;
    using int_type  = typename details::integer_type<T>::type;
    using simd_int  = simd<int_type, Bits, scalar_nosimd_tag>;

    force_inline
    static simd_type eval(const simd_type& k)
    {
        return simd_type(matcl::simd::scalar_func::fraction(k.data));
    };
};

//-----------------------------------------------------------------------
//                          exponent
//-----------------------------------------------------------------------
template<class T, int Bits>
struct simd_exponent<T, Bits, nosimd_tag>
{
    using simd_type = simd<T, Bits, nosimd_tag>;
    using int_type  = typename details::integer_type<T>::type;
    using simd_int  = simd<int_type, Bits, nosimd_tag>;

    static const int 
    vector_size     = simd_type::vector_size;

    force_inline
    static simd_type eval(const simd_type& k)
    {
        simd_type res;

        for (int i = 0; i < vector_size; ++i)
            res.data[i] = matcl::simd::scalar_func::exponent(k.data[i]);

        return res;
    };

    force_inline
    static simd_int eval_i(const simd_type& k)
    {
        simd_int res;

        for (int i = 0; i < vector_size; ++i)
            res.data[i] = matcl::simd::scalar_func::iexponent(k.data[i]);

        return res;
    };
};

template<class T, int Bits>
struct simd_exponent<T, Bits, scalar_nosimd_tag>
{
    using simd_type = simd<T, Bits, scalar_nosimd_tag>;
    using int_type  = typename details::integer_type<T>::type;
    using simd_int  = simd<int_type, Bits, scalar_nosimd_tag>;

    force_inline
    static simd_type eval(const simd_type& k)
    {
        return simd_type(matcl::simd::scalar_func::exponent(k.data));
    };

    force_inline
    static simd_int eval_i(const simd_type& k)
    {
        return simd_int(matcl::simd::scalar_func::iexponent(k.data));
    };
};

//-----------------------------------------------------------------------
//                          copysign
//-----------------------------------------------------------------------
template<class T, int Bits>
struct simd_copysign<T, Bits, nosimd_tag>
{
    using simd_type = simd<T, Bits, nosimd_tag>;

    static const int 
    vector_size     = simd_type::vector_size;

    force_inline
    static simd_type eval(const simd_type& x, const simd_type& y)
    {
        simd_type res;

        for (int i = 0; i < vector_size; ++i)
            res.data[i] = matcl::simd::scalar_func::copysign(x.data[i], y.data[i]);

        return res;
    };
};

template<class T, int Bits>
struct simd_copysign<T, Bits, scalar_nosimd_tag>
{
    using simd_type = simd<T, Bits, scalar_nosimd_tag>;

    force_inline
    static simd_type eval(const simd_type& x, const simd_type& y)
    {
        return simd_type(matcl::simd::scalar_func::copysign(x.data, y.data));
    };
};

//-----------------------------------------------------------------------
//                          sincos
//-----------------------------------------------------------------------
template<int Bits>
struct simd_sincos<double, Bits, nosimd_tag>
{
    using simd_type     = simd<double, Bits, nosimd_tag>;

    force_inline
    static simd_type eval_sin(const simd_type& a)
    {
        static const 
        int vec_size    = simd_type::vector_size;

        simd_type res;

        const double* ptr_a = a.get_raw_ptr();
        double* ptr_res     = res.get_raw_ptr();

        for (int i = 0; i < vec_size; ++i)
            ptr_res[i]      = ms::sin(ptr_a[i]);

        return res;
    };

    force_inline
    static simd_type eval_cos(const simd_type& a)
    {
        static const 
        int vec_size    = simd_type::vector_size;

        simd_type res;

        const double* ptr_a = a.get_raw_ptr();
        double* ptr_res     = res.get_raw_ptr();

        for (int i = 0; i < vec_size; ++i)
            ptr_res[i]      = ms::cos(ptr_a[i]);

        return res;
    };
};

template<int Bits>
struct simd_sincos<float, Bits, nosimd_tag>
{
    using simd_type     = simd<float, Bits, nosimd_tag>;

    force_inline
    static simd_type eval_sin(const simd_type& a)
    {
        static const 
        int vec_size    = simd_type::vector_size;

        simd_type res;

        const float* ptr_a  = a.get_raw_ptr();
        float* ptr_res      = res.get_raw_ptr();

        for (int i = 0; i < vec_size; ++i)
            ptr_res[i]      = ms::sin(ptr_a[i]);

        return res;
    };

    force_inline
    static simd_type eval_cos(const simd_type& a)
    {
        static const 
        int vec_size    = simd_type::vector_size;

        simd_type res;

        const float* ptr_a  = a.get_raw_ptr();
        float* ptr_res      = res.get_raw_ptr();

        for (int i = 0; i < vec_size; ++i)
            ptr_res[i]      = ms::cos(ptr_a[i]);

        return res;
    };
};

//-----------------------------------------------------------------------
//                          tan/cot
//-----------------------------------------------------------------------
template<int Bits>
struct simd_tancot<double, Bits, nosimd_tag>
{
    using simd_type     = simd<double, Bits, nosimd_tag>;

    force_inline
    static simd_type eval_tan(const simd_type& a)
    {
        static const 
        int vec_size    = simd_type::vector_size;

        simd_type res;

        const double* ptr_a = a.get_raw_ptr();
        double* ptr_res     = res.get_raw_ptr();

        for (int i = 0; i < vec_size; ++i)
            ptr_res[i]      = ms::tan(ptr_a[i]);

        return res;
    };

    force_inline
    static simd_type eval_cot(const simd_type& a)
    {
        static const 
        int vec_size    = simd_type::vector_size;

        simd_type res;

        const double* ptr_a = a.get_raw_ptr();
        double* ptr_res     = res.get_raw_ptr();

        for (int i = 0; i < vec_size; ++i)
            ptr_res[i]      = ms::cot(ptr_a[i]);

        return res;
    };
};

template<int Bits>
struct simd_tancot<float, Bits, nosimd_tag>
{
    using simd_type     = simd<float, Bits, nosimd_tag>;

    force_inline
    static simd_type eval_tan(const simd_type& a)
    {
        static const 
        int vec_size    = simd_type::vector_size;

        simd_type res;

        const float* ptr_a  = a.get_raw_ptr();
        float* ptr_res      = res.get_raw_ptr();

        for (int i = 0; i < vec_size; ++i)
            ptr_res[i]      = ms::tan(ptr_a[i]);

        return res;
    };

    force_inline
    static simd_type eval_cot(const simd_type& a)
    {
        static const 
        int vec_size    = simd_type::vector_size;

        simd_type res;

        const float* ptr_a  = a.get_raw_ptr();
        float* ptr_res      = res.get_raw_ptr();

        for (int i = 0; i < vec_size; ++i)
            ptr_res[i]      = ms::cot(ptr_a[i]);

        return res;
    };
};

}}}
