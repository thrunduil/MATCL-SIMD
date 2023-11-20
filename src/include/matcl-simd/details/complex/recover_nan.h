/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/config.h"
#include "matcl-simd/complex/complex_details.h"
#include "matcl-simd/details/scalfunc_real.h"

namespace matcl { namespace simd { namespace details
{

namespace mrd = matcl::raw::details;

template<class T>
struct recover_nan_mul
{};

template<class T>
struct recover_nan_div
{};

template<class T>
struct recover_nan_div_rc
{};

template<>
struct recover_nan_mul<double>
{
    using complex_type  = simd_double_complex;
    using matcl_complex = Complex;

    static complex_type eval(const complex_type& x, const complex_type& y,
                                    double r_re, double r_im)
    {
        using impl_type = md::mul_helper<Complex, Complex>;

        if (mrd::scal_func::isnan(r_re) == false || mrd::scal_func::isnan(r_im) == false)
            return complex_type(r_re, r_im);

        matcl_complex mx(real(x), imag(x));
        matcl_complex my(real(y), imag(y));

        matcl_complex ret = impl_type::recover_nan(mx, my, r_re, r_im);
        return complex_type(real(ret), imag(ret));
    };
};

template<>
struct recover_nan_mul<float>
{
    using complex_type  = simd_single_complex;
    using matcl_complex = Float_complex;

    static complex_type eval(const complex_type& x, const complex_type& y,
                                    float r_re, float r_im)
    {
        using impl_type = md::mul_helper<Float_complex, Float_complex>;

        if (mrd::scal_func::isnan(r_re) == false || mrd::scal_func::isnan(r_im) == false)
            return complex_type(r_re, r_im);

        matcl_complex mx(real(x), imag(x));
        matcl_complex my(real(y), imag(y));

        matcl_complex ret = impl_type::recover_nan(mx, my, r_re, r_im);
        return complex_type(real(ret), imag(ret));

    };
};


template<>
struct recover_nan_div<double>
{
    using complex_type  = simd_double_complex;
    using matcl_complex = Complex;

    static complex_type eval(const complex_type& x, const complex_type& y)
    {
        using impl_type = md::div_helper<Complex, Complex>;

        matcl_complex mx(real(x), imag(x));
        matcl_complex my(real(y), imag(y));

        matcl_complex ret = impl_type::eval(mx, my);
        return complex_type(real(ret), imag(ret));
    };
};

template<>
struct recover_nan_div<float>
{
    using complex_type  = simd_single_complex;
    using matcl_complex = Float_complex;

    static complex_type eval(const complex_type& x, const complex_type& y)
    {
        using impl_type = md::div_helper<Float_complex, Float_complex>;

        matcl_complex mx(real(x), imag(x));
        matcl_complex my(real(y), imag(y));

        matcl_complex ret = impl_type::eval(mx, my);
        return complex_type(real(ret), imag(ret));

    };
};


template<>
struct recover_nan_div_rc<double>
{
    using complex_type  = simd_double_complex;
    using matcl_complex = Complex;

    static complex_type eval(double x, const complex_type& y)
    {
        using impl_type = md::div_helper<double, Complex>;

        matcl_complex my(real(y), imag(y));

        matcl_complex ret = impl_type::eval(x, my);
        return complex_type(real(ret), imag(ret));
    };
};

template<>
struct recover_nan_div_rc<float>
{
    using complex_type  = simd_single_complex;
    using matcl_complex = Float_complex;

    static complex_type eval(float x, const complex_type& y)
    {
        using impl_type = md::div_helper<float, Float_complex>;

        matcl_complex my(real(y), imag(y));

        matcl_complex ret = impl_type::eval(x, my);
        return complex_type(real(ret), imag(ret));

    };
};

}}}