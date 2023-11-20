/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "test_simd_config.h"
#include "matcl-simd/simd.h"
#include "utils.h"

#include <string>

namespace matcl { namespace test
{

void test_performance_int_scalar();
void test_values_int_scalar();

class test_simd_scalar_int
{
    private:
        std::string m_instr_tag;
        bool        m_test_values;

    public:
        test_simd_scalar_int(bool test_values);

        void    make_ternary();
        void    make_binary();
        void    make_unary();
        void    make_unary_int();

    private:
        int     get_size() const;
        int     get_size_perf() const;
        int     get_num_rep() const;

        template<class T>
        bool    test_equal(int size, const T* res, const T* res_gen);

        template<class T>
        bool    test_equal(const T& res, const T& res_gen);

        template<class T>
        void    test_functions();

        template<class T>
        void    test_functions_int();

        template<class T>
        void    test_functions_bin();

        template<class T>
        void    test_functions_3();

        template<class T, class Func>
        void    test_function(formatted_disp& fd, int size, const T* in, 
                    T* out, T* out_gen);

        template<class T, class T_int, class Func>
        void    test_function_int(formatted_disp& fd, int size, const T_int* in, 
                    T* out, T* out_gen, const Func& func);

        template<class T, class Func>
        void    test_function_bin(formatted_disp& fd, int size, const T* in_1, 
                    const T* in_2, T* out, T* out_gen);

        template<class T, class Func>
        void    test_function_3(formatted_disp& fd, int size, const T* in_1, 
                    const T* in_2, const T* in_3, T* out, T* out_gen);

        template<class T, class Func>
        void    test_function_block(formatted_disp& fd, int size, const T* in, 
                    T* out, T* out_gen);

        template<class T, class Simd_type, class Func>
        double  test_function_simd(int size, int n_rep, const T* in, T* out);

        template<class T, class Int_type, class Simd_type, class Func>
        double  test_function_simd_int(int size, int n_rep, const Int_type* in, T* out, const Func& f);

        template<class T, class Simd_type, class Func>
        double  test_function_bin_simd(int size, int n_rep, const T* in1, const T* in2, T* out);

        template<class T, class Simd_type, class Func>
        double  test_function_3_simd(int size, int n_rep, const T* in1, const T* in2, const T* in3, T* out);

        template<class T, class Func>
        double  test_function_generic(int size, int n_rep, const T* in, T* out);
};

}}
