/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/simd.h"

namespace matcl { namespace simd
{

//-----------------------------------------------------------------------
//                      EVALUATION OF POLYNOMIALS
//-----------------------------------------------------------------------
// evaluation of a polynomial P(x) = sum_{i = 0}^{N - 1} a_i * x^i

// Template arguments:
//  N           - number of coefficients of the polynomial
//  Arg_type    - floating point type (float, double, or a simd type)
//  Coef_type   - floating point type of polynomial coefficients,
//                  this type must be convertible to Arg_type

// Notation:
//  u is the unit roundoff (half of the machine epsilon)
//  gam(k) = k/(1-ku)

//-----------------------------------------------------------------------
//                      HORNER SCHEME
//-----------------------------------------------------------------------

// evaluate a polynomial at point x using the Horner's scheme
//      res = small_horner(x, a0, a1, ..., a_N-1)
// where ai is the i-th coefficientof the polynomial
//
// Template arguments:
//  Arg_type    - floating point type (float, double, or a simd type)
//  Args...     - floating point type of a polynomial coefficient,
//                  this type must be convertible to Arg_type
template<class Arg_type, class ... Args>
force_inline
Arg_type    small_horner(const Arg_type& x, const Args& ... coef);

// evaluate a polynomial at point x using the Horner's scheme
// polynomial is represented as an array of size N:
//      poly = {a_0, a_1, ..., a_{N-1}}
template<int N, class Arg_type, class Coef_type>
force_inline
Arg_type    horner(const Arg_type& x, const Coef_type* poly);

// evaluate a polynomial at point x using the Horner's scheme
// polynomial is represented as an array of size N:
//      poly = {a_0, a_1, ..., a_{N-1}}
template<class Arg_type, class Coef_type>
Arg_type    horner(const Arg_type& x, int N, const Coef_type* poly);

// evaluate a polynomial at point x using the Horner's scheme
// polynomial is represented as an array of size N:
//      poly = {a_0, a_1, ..., a_{N-1}}
// this function also returns aposteriori absolute forward error
// estimator 'error', such that:
//      |res - p(x) | <= 'error'
// where res is the computed value, p(x) is true value
template<class Arg_type, class Coef_type>
Arg_type    horner_and_error(const Arg_type& x, int N, const Coef_type* poly,
                Arg_type& error);

// return a priori condition number of a polynomial at point x evaluated using
// the Horner's method. 
// The relative accuracy of computed polynomial p_ap(x) is given by
//      |p(x) - p_ap(x)| / |p(x)| <= a(2N-2) * cond(p, x) * u + O(u^2)
// where p(x) is the true value, cond(p, x) is returned condition number.
//
// The condition number cond(p, x) is given by:
//      cond(p, x) = (sum_{i = 0}^{N - 1} |a_i| * |x|^i) / |p(x)| 
//                := |p|(|x|) / p(x)
//
// optionally, the function returns value of the polynomial p(x) returned in 'val'
// argument, value of |p|(|x|) returned in 'abs_val' argument
//
// Note:
//  This is a priori bound and so takes no account of the actual rounding
//  errors that occur, therefore can be too pessimistic. Additionally, in denominator
//  computed value of p_ap(x) is used as an approximation of true value p(x).
template<class Arg_type, class Coef_type>
Arg_type    horner_apriori_cond(const Arg_type& x, int N, const Coef_type* poly);

template<class Arg_type, class Coef_type>
Arg_type    horner_apriori_cond(const Arg_type& x, int N, const Coef_type* poly,
                Arg_type& val, Arg_type& abs_val);

// return aposteriori condition number of a polynomial at point x evaluated using
// the Horner's method defined as 
//      |p(x) - p_ap(x)| / |p(x)| <= post_cond(p, x) * u
// where p(x) is the true value, post_cond(p, x) is returned condition number.
//
// The condition number post_cond(p, x) is calculated using the horner_and_error
// function.
//
// optionally, the function returns computed value of the polynomial p_app(x) 
// returned in 'val' argument and estimated error, such that |p(x) - p_ap(x)| <= error
// in 'err' argument.
//
// Note:
//  This condition number of more accurate than condition number returned by
//  horner_apriori_cond, since it takes into account actual rounding errors.
//  The function may return negative condition number if computed value p_app is very
//  inaccurate, i.e. when |p_app(x)| < err.
template<class Arg_type, class Coef_type>
Arg_type    horner_aposteriori_cond(const Arg_type& x, int N, const Coef_type* poly);

template<class Arg_type, class Coef_type>
Arg_type    horner_aposteriori_cond(const Arg_type& x, int N, const Coef_type* poly,
                Arg_type& val, Arg_type& err);

//-----------------------------------------------------------------------
//                      ESTRIN SCHEME
//-----------------------------------------------------------------------

// evaluate a polynomial at point x using the Estrin's scheme
// polynomial is represented as an array of size N:
//      poly = {a_0, a_1, ..., a_{N-1}}
//
// Note:
//  this function is generally faster than horner function for 
//  sufficiently large polynomials (N > 10), but is less accurate
template<int N, class Arg_type, class Coef_type>
force_inline
Arg_type    estrin(const Arg_type& x, const Coef_type* poly);

// evaluate a polynomial at point x using the Horner's scheme
// polynomial is represented as an array of size N:
//      poly = {a_0, a_1, ..., a_{N-1}}
//
// Note:
//  this function can be must faster than horner function for 
//  sufficiently large polynomials (N > 100), but is less accurate.
template<class Arg_type, class Coef_type>
Arg_type    estrin(const Arg_type& x, int N, const Coef_type* poly);

}};

#include "matcl-simd/details/poly/poly_eval.inl"
