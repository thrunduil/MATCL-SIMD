/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/poly/poly_eval.h"
#include "matcl-simd/details/float/twofold.h"

namespace matcl { namespace simd
{

//-----------------------------------------------------------------------
//                      COMPENSATED HORNER
//-----------------------------------------------------------------------

// evaluate a polynomial at point x using the compensated Horner's scheme
// polynomial is represented as an array of size N:
//      poly = {a_0, a_1, ..., a_{N-1}}
// return twofold number r + e = p(x)
//
// Note:
//  this function is evaluates a polynomial with high accuracy:
//      |p(x) - r|/|p(x)|       <= u + a(2N-2)^2 * cond(p,x) * u^2
//      |p(x) - (r + e)|/|p(x)| <= a(2N-2)^2 * cond(p,x) * u^2
// where p(x) is the true value, cond(p,x) is the condition number of p as
// returned by horner_apriori_cond function.
// Thus, if p is not too ill-conditioned, then p(x) is calculated with nearly 
// full accuracy. This function is however more costly, than the  horner 
// function (3-8 times slower)
//
// References:
//  [1]. Faithful Polynomial Evaluation with Compensated Horner Algorithm,
//      P. Langlois, N. Louvet, 2006
template<class Arg_type, class Coef_type>
twofold<Arg_type>
            compensated_horner(const Arg_type& x, int N, const Coef_type* poly);

// evaluate a polynomial at point x using the compensated Horner's scheme
// polynomial is represented as an array of size N with twofold arguments:
//      poly = {a_0, a_1, ..., a_{N-1}}
// return twofold number r + e = p(x)
//
// Note:
//  this function is evaluates a polynomial with high accuracy:
//      |p(x) - r|/|p(x)|       <= u + a((N-1)c) * cond(p,x) * u^2
//      |p(x) - (r + e)|/|p(x)| <= a((N-1)c) * cond(p,x) * u^2
// where p(x) is the true value, cond(p,x) is the condition number of p as
// returned by horner_apriori_cond function, and c = 10 if x is a twofold
// number and c = 6 otherwise.
// Thus, if p is not too ill-conditioned, then p(x) is calculated with nearly 
// full accuracy. This function is however more costly, than the  horner 
// function (3-8 times slower)
//
// References:
//  [1]. Faithful Polynomial Evaluation with Compensated Horner Algorithm,
//      P. Langlois, N. Louvet, 2006
template<class Arg_type, class Coef_type>
twofold<Arg_type>
            compensated_horner(const twofold<Arg_type>& x, int N, const twofold<Coef_type>* poly);

template<class Arg_type, class Coef_type>
twofold<Arg_type>
            compensated_horner(const Arg_type& x, int N, const twofold<Coef_type>* poly);

// evaluate a polynomial at point x using the compensated Horner's scheme
// as in case of the function compensated_horner function; polynomial is 
// represented as an array of size N:
//      poly = {a_0, a_1, ..., a_{N-1}}
// this function also returns aposteriori absolute forward error
// estimator 'error', such that:
//      |res - p(x) | <= 'error'
// where res is the computed value, p(x) is true value
// if returned value of 'is_faithfully_rounded' argument is true, then the
// result is proven to be one of two floating point value closest to true
// value.
//
// References:
//  [1]. Faithful Polynomial Evaluation with Compensated Horner Algorithm,
//      P. Langlois, N. Louvet, 2006
template<class Arg_type, class Coef_type>
Arg_type    compensated_horner_and_error(const Arg_type& x, int N, const Coef_type* poly,
                Arg_type& error, bool& is_faithfully_rounded);

}};

#include "matcl-simd/details/poly/poly_eval_twofold.inl"
