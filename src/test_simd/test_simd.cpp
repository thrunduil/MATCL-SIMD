/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#include "test_simd_config.h"
#include "test_simd.h"
#include "utils.h"

#include "matcl-simd/simd.h"
#include "matcl-simd/simd_math.h"
#include "test_functions.h"
#include <vector>

namespace matcl { namespace test
{

namespace ms = matcl::simd;

void test::test_performance_real()
{   
    test_simd(false).make_unary_math();
    test_simd(false).make_combine();
    test_simd(false).make_select();    
    test_simd(false).make_unary();
    test_simd(false).make_unary_int();
    test_simd(false).make_ternary();
    test_simd(false).make_binary();
};

void test::test_values_real()
{
    test_simd(true).make_unary();
    test_simd(true).make_unary_math();
    test_simd(true).make_combine();
    test_simd(true).make_select();        
    test_simd(true).make_ternary();        
    test_simd(false).make_unary_int();
    test_simd(true).make_binary();        
};

template<class T>
bool test_simd::test_equal(const T& res, const T& res_gen, double max_dist, double& dist, bool check_nans)
{
    dist = 0.0;

    if (res == res_gen)
        return true;

    if (is_nan(res) && is_nan(res_gen))
        return true;

    dist = float_distance(res, res_gen);

    if (is_nan(dist) == true)
        return check_nans ? false : true;

    if (dist > max_dist)
        return false;
    else
        return true;
}

template<class T>
bool test_simd::test_equal(int size, const T* res, const T* res_gen, double max_dist, double& dist,
                        bool check_nans)
{
    bool eq         = true;
    dist            = 0.0;

    double loc_dist;

    for (int i = 0; i < size; ++i)
    {
        bool tmp    = test_equal(res[i], res_gen[i], max_dist, loc_dist, check_nans);

        /*
        if (tmp == false)
        {
            std::cout << i << " " << res[i] << " " << res_gen[i] << " " << loc_dist << "\n";
        }
        */

        eq          = eq && tmp;
        dist        = std::max(dist, loc_dist);
    };

    return eq;
}

test_simd::test_simd(bool test_values)
    :m_instr_tag(MATCL_TEST_SIMD_TAG), m_test_values(test_values)
{};

void test_simd::make_unary()
{
    test_functions<float>(); 
    test_functions<double>();       
};

void test_simd::make_unary_math()
{
    test_functions_math<float>();
    test_functions_math<double>();    
};

void test_simd::make_select()
{
    test_functions_select<float>(); 
    test_functions_select<double>();       
};

void test_simd::make_combine()
{
    test_functions_combine<float>(); 
    test_functions_combine<double>();       
};

void test_simd::make_unary_int()
{
    test_functions_int<float>();   
    test_functions_int<double>();     
};

void test_simd::make_binary()
{
    test_functions_bin<double>();
    test_functions_bin<float>();
};

void test_simd::make_ternary()
{
    test_functions_3<double>();
    test_functions_3<float>();    
};

template<class T, class Simd_type, class Func>
double test_simd::test_function_simd(int size, int n_rep, const T* in, T* out)
{
    static const int vec_size   = Simd_type::vector_size;

    tic();

    volatile T val = 0;

    for(int j = 0; j < n_rep; ++j)
    {
        for (int i = 0; i < size; i += vec_size)
        {
            Simd_type x     = Simd_type::load(in + i, std::false_type());
            Simd_type res   = Func::eval(x);

            res.store(out + i, std::false_type());
        };

        val += out[0];
    };

    double t = toc();
    return t;
};

template<class T, class Func>
double test_simd::test_function_std(int size, int n_rep, const T* in, T* out)
{
    tic();

    volatile T val = 0;

    for(int j = 0; j < n_rep; ++j)
    {
        for (int i = 0; i < size; i += 1)
        {
            T x     = in[i];
            T res   = Func::eval_base(x);

            out[i]  = res;
            val     += res;
        };        
    };

    double t = toc();
    return t;
};

template<class T, class Func>
double test_simd::test_function_mat_ref(int, int, const T*, T*)
{
    return 0.0;
};

template<class T, class Int_type, class Simd_type, class Func>
double test_simd::test_function_simd_int(int size, int n_rep, const Int_type* in, T* out, const Func& func)
{
    static const int vec_size   = Simd_type::vector_size;

    static const int bits       = Simd_type::number_bits;
    using simd_tag              = typename Simd_type::simd_tag;
    using Simd_type_int         = matcl::simd::simd<Int_type, bits, simd_tag>;

    (void)func;

    tic();

    volatile T val = 0;

    for(int j = 0; j < n_rep; ++j)
    {
        for (int i = 0; i < size; i += vec_size)
        {
            Simd_type_int x = Simd_type_int::load(in + i, std::false_type());
            Simd_type res   = func.eval(x);

            res.store(out + i, std::false_type());
        };

        val += out[0];
    };

    double t = toc();
    return t;
};

template<class T, class Simd_type, class Func>
double test_simd::test_function_bin_simd(int size, int n_rep, const T* in1, const T* in2, T* out)
{
    static const int vec_size   = Simd_type::vector_size;

    tic();

    volatile T val = 0;

    for(int j = 0; j < n_rep; ++j)
    {
        for (int i = 0; i < size; i += vec_size)
        {
            Simd_type x1    = Simd_type::load(in1 + i, std::false_type());
            Simd_type x2    = Simd_type::load(in2 + i, std::false_type());

            Simd_type res   = Func::eval(x1, x2);

            res.store(out + i, std::false_type());
        };

        val += out[0];
    };

    double t = toc();
    return t;
};

template<class T, class Simd_type, class Func>
double test_simd::test_function_3_simd(int size, int n_rep, const T* in1, const T* in2, 
                                              const T* in3, T* out)
{
    static const int vec_size   = Simd_type::vector_size;

    tic();

    volatile T val = 0;

    for(int j = 0; j < n_rep; ++j)
    {
        for (int i = 0; i < size; i += vec_size)
        {
            Simd_type x1    = Simd_type::load(in1 + i, std::false_type());
            Simd_type x2    = Simd_type::load(in2 + i, std::false_type());
            Simd_type x3    = Simd_type::load(in3 + i, std::false_type());

            Simd_type res   = Func::eval(x1, x2, x3);

            res.store(out + i, std::false_type());
        };

        val += out[0];
    };

    double t = toc();
    return t;
};

template<class T, class Func>
double test_simd::test_function_generic(int size, int n_rep, const T* in, T* out)
{
    tic();

    volatile T val = 0;

    for(int j = 0; j < n_rep; ++j)
    {
        for (int i = 0; i < size; i += 1)
        {
            out[i]  = Func::eval(in[i]);
        };

        val += out[0];
    };

    double t = toc();
    return t;
};

template<class T, class Func>
void test_simd::test_function(formatted_disp& fd, int size, const T* in, T* out, T* out_gen, 
                        bool check_nans)
{
    double t0, t1, t2, t3, t4, t5;
    bool v1, v2, v3, v4, v5;
    double d1, d2, d3, d4, d5;

    t0  = test_function_simd<T, ms::simd<T, 128, ms::nosimd_tag>, Func>(size, 1, in, out_gen);

    t1  = test_function_simd<T, simd::simd<T, 128, simd::nosimd_tag>, Func>(size, 1, in, out);
    v1  = test_equal(size, out, out_gen, 1.0, d1, check_nans);

    t2  = test_function_simd<T, simd::simd<T, 256, simd::nosimd_tag>, Func>(size, 1, in, out);
    v2  = test_equal(size, out, out_gen, 1.0, d2, check_nans);

    t3  = test_function_simd<T, simd::simd<T, 128, simd::sse_tag>, Func>(size, 1, in, out);    
    v3  = test_equal(size, out, out_gen, 1.0, d3, check_nans);

    t4  = test_function_simd<T, simd::simd<T, 256, simd::sse_tag>, Func>(size, 1, in, out);
    v4  = test_equal(size, out, out_gen, 1.0, d4, check_nans);

    #if MATCL_ARCHITECTURE_HAS_AVX
        t5  = test_function_simd<T, simd::simd<T, 256, simd::avx_tag>, Func>(size, 1, in, out);    
        v5  = test_equal(size, out, out_gen, 1.0, d5, check_nans);
    #else
        t5  = t0;
        v5  = true;
        d5  = 0;
    #endif

    bool ok = v1 && v2 && v3 && v4 && v5;

    int N       = get_size_perf();
    int M       = get_num_rep();

    t0  = test_function_simd<T, ms::simd<T, 128, ms::nosimd_tag>, Func>(N, M, in, out_gen);
    t1  = test_function_simd<T, simd::simd<T, 128, simd::nosimd_tag>, Func>(N, M, in, out);
    t2  = test_function_simd<T, simd::simd<T, 256, simd::nosimd_tag>, Func>(N, M, in, out);
    t3  = test_function_simd<T, simd::simd<T, 128, simd::sse_tag>, Func>(N, M, in, out);    
    t4  = test_function_simd<T, simd::simd<T, 256, simd::sse_tag>, Func>(N, M, in, out);

    #if MATCL_ARCHITECTURE_HAS_AVX
        t5  = test_function_simd<T, simd::simd<T, 256, simd::avx_tag>, Func>(N, M, in, out);    
    #else
        t5 = t0;
    #endif

    std::string status  = (ok == true) ? "OK" : "FAIL"; 
    fd.disp_row(Func::name(), t0, t0/t1, t0/t2, t0/t3, t0/t4, t0/t5, status);
};

template<class T, class Func>
void test_simd::test_function_math(formatted_disp& fd, int size, const T* in, T* out, T* out_gen, 
                                bool check_nans)
{
    double t0, t1, t2, t3, t4, t5;
    bool v0, v1, v2, v3, v4, v5;
    double d0, d1, d2, d3, d4, d5;

    t0  = test_function_mat_ref<T, Func>(size, 1, in, out_gen);

    v0  = true;
    d0  = 0;

    t1  = test_function_simd<T, simd::simd<T, 128, simd::nosimd_tag>, Func>(size, 1, in, out);
    v1  = test_equal(size, out, out_gen, 1.0, d1, check_nans);

    t2  = test_function_simd<T, simd::simd<T, 256, simd::nosimd_tag>, Func>(size, 1, in, out);
    v2  = test_equal(size, out, out_gen, 1.0, d2, check_nans);

    t3  = test_function_simd<T, simd::simd<T, 128, simd::sse_tag>, Func>(size, 1, in, out);    
    v3  = test_equal(size, out, out_gen, 1.0, d3, check_nans);

    t4  = test_function_simd<T, simd::simd<T, 256, simd::sse_tag>, Func>(size, 1, in, out);
    v4  = test_equal(size, out, out_gen, 1.0, d4, check_nans);

    #if MATCL_ARCHITECTURE_HAS_AVX
        t5  = test_function_simd<T, simd::simd<T, 256, simd::avx_tag>, Func>(size, 1, in, out);    
        v5  = test_equal(size, out, out_gen, 1.0, d5, check_nans);
    #else
        t5  = t0;
        v5  = true;
        d5  = 0;
    #endif

    bool ok = v0 && v1 && v2 && v3 && v4 && v5;

    int N       = get_size_perf();
    int M       = get_num_rep();

    t0  = test_function_std<T, Func>(N, M, in, out_gen);
    t1  = test_function_simd<T, simd::simd<T, 128, simd::nosimd_tag>, Func>(N, M, in, out);
    t2  = test_function_simd<T, simd::simd<T, 256, simd::nosimd_tag>, Func>(N, M, in, out);
    t3  = test_function_simd<T, simd::simd<T, 128, simd::sse_tag>, Func>(N, M, in, out);    
    t4  = test_function_simd<T, simd::simd<T, 256, simd::sse_tag>, Func>(N, M, in, out);

    #if MATCL_ARCHITECTURE_HAS_AVX
        t5  = test_function_simd<T, simd::simd<T, 256, simd::avx_tag>, Func>(N, M, in, out);    
    #else
        t5  = t0;
    #endif

    std::string status  = (ok == true) ? "OK" : "FAIL"; 
    fd.disp_row(Func::name(), t0, t0/t1, t0/t2, t0/t3, t0/t4, t0/t5, status);
};

template<class T, class T_int, class Func>
void test_simd::test_function_int(formatted_disp& fd, int size, const T_int* in, T* out, T* out_gen,
                                const Func& func)
{
    double t0, t1, t2, t3, t4, t5;
    bool v1, v3, v4, v5;
    double d1, d3, d4, d5;

    t0  = test_function_simd_int<T, T_int, ms::simd<T, 128, ms::nosimd_tag>, Func>(size, 1, in, out_gen, func);

    t1  = test_function_simd_int<T, T_int, simd::simd<T, 128, simd::nosimd_tag>, Func>(size, 1, in, out, func);
    v1  = test_equal(size, out, out_gen, 1.0, d1, true);

    t3  = test_function_simd_int<T, T_int, simd::simd<T, 128, simd::sse_tag>, Func>(size, 1, in, out, func);    
    v3  = test_equal(size, out, out_gen, 1.0, d3, true);

    t2  = test_function_simd_int<T, T_int, simd::simd<T, 256, simd::nosimd_tag>, Func>(size, 1, in, out_gen, func);

    t4  = test_function_simd_int<T, T_int, simd::simd<T, 256, simd::sse_tag>, Func>(size, 1, in, out, func);
    v4  = test_equal(size, out, out_gen, 1.0, d4, true);

    #if MATCL_ARCHITECTURE_HAS_AVX
        t5  = test_function_simd_int<T, T_int, simd::simd<T, 256, simd::avx_tag>, Func>(size, 1, in, out, func);    
        v5  = test_equal(size, out, out_gen, 1.0, d5, true);
    #else
        t5  = t0;
        v5  = true;
        d5  = 0;
    #endif

    bool ok = v1 && v3 && v4 && v5;

    int N       = get_size_perf();
    int M       = get_num_rep();

    t0  = test_function_simd_int<T, T_int, ms::simd<T, 128, ms::nosimd_tag>, Func>(N, M, in, out_gen, func);
    t1  = test_function_simd_int<T, T_int, simd::simd<T, 128, simd::nosimd_tag>, Func>(N, M, in, out, func);
    t2  = test_function_simd_int<T, T_int, simd::simd<T, 256, simd::nosimd_tag>, Func>(N, M, in, out, func);
    t3  = test_function_simd_int<T, T_int, simd::simd<T, 128, simd::sse_tag>, Func>(N, M, in, out, func);    
    t4  = test_function_simd_int<T, T_int, simd::simd<T, 256, simd::sse_tag>, Func>(N, M, in, out, func);

    #if MATCL_ARCHITECTURE_HAS_AVX
        t5  = test_function_simd_int<T, T_int, simd::simd<T, 256, simd::avx_tag>, Func>(N, M, in, out, func);    
    #else
        t5  = t0;
    #endif

    std::string status  = (ok == true) ? "OK" : "FAIL"; 
    fd.disp_row(Func::name(), t0, t0/t1, t0/t2, t0/t3, t0/t4, t0/t5, status);
};

template<class T, class Func>
void test_simd::test_function_bin(formatted_disp& fd, int size, const T* in_1, 
                                  const T* in_2, T* out, T* out_gen)
{
    double t0, t1, t2, t3, t4, t5;
    bool v1, v2, v3, v4, v5;
    double d1, d2, d3, d4, d5;

    t0  = test_function_bin_simd<T, simd::simd<T, 128, simd::nosimd_tag>, Func>(size, 1, in_1, in_2, out_gen);

    t1  = test_function_bin_simd<T, simd::simd<T, 128, simd::nosimd_tag>, Func>(size, 1, in_1, in_2, out);
    v1  = test_equal(size, out, out_gen, 1.0, d1, true);

    t2  = test_function_bin_simd<T, simd::simd<T, 256, simd::nosimd_tag>, Func>(size, 1, in_1, in_2, out);
    v2  = test_equal(size, out, out_gen, 1.0, d2, true);

    t3  = test_function_bin_simd<T, simd::simd<T, 128, simd::sse_tag>, Func>(size, 1, in_1, in_2, out);    
    v3  = test_equal(size, out, out_gen, 1.0, d3, true);

    t4  = test_function_bin_simd<T, simd::simd<T, 256, simd::sse_tag>, Func>(size, 1, in_1, in_2, out);
    v4  = test_equal(size, out, out_gen, 1.0, d4, true);

    #if MATCL_ARCHITECTURE_HAS_AVX
        t5  = test_function_bin_simd<T, simd::simd<T, 256, simd::avx_tag>, Func>(size, 1, in_1, in_2, out);    
        v5  = test_equal(size, out, out_gen, 1.0, d5, true);
    #else
        t5  = t0;
        v5  = true;
        d5  = 0;
    #endif

    bool ok = v1 && v2 && v3 && v4 && v5;

    int N       = get_size_perf();
    int M       = get_num_rep();

    t0  = test_function_bin_simd<T, simd::simd<T, 128, simd::nosimd_tag>, Func>
                (N, M, in_1, in_2, out_gen);
    t1  = test_function_bin_simd<T, simd::simd<T, 128, simd::nosimd_tag>, Func>
                (N, M, in_1, in_2, out);
    t2  = test_function_bin_simd<T, simd::simd<T, 256, simd::nosimd_tag>, Func>
                (N, M, in_1, in_2, out);
    t3  = test_function_bin_simd<T, simd::simd<T, 128, simd::sse_tag>, Func>
                (N, M, in_1, in_2, out);    
    t4  = test_function_bin_simd<T, simd::simd<T, 256, simd::sse_tag>, Func>
                (N, M, in_1, in_2, out);

    #if MATCL_ARCHITECTURE_HAS_AVX
        t5  = test_function_bin_simd<T, simd::simd<T, 256, simd::avx_tag>, Func>
                (N, M, in_1, in_2, out);    
    #else
        t5  = t0;
    #endif

    std::string status  = (ok == true) ? "OK" : "FAIL"; 
    fd.disp_row(Func::name(), t0, t0/t1, t0/t2, t0/t3, t0/t4, t0/t5, status);
};

template<class T, class Func>
void test_simd::test_function_combine(formatted_disp& fd, int size, const T* in_1, 
                                  const T* in_2, T* out, T* out_gen, bool check_nans)
{
    double t0, t1, t3;
    bool v1, v3;
    double d1, d3;

    t0  = test_function_bin_simd<T, simd::simd<T, 128, simd::nosimd_tag>, Func>(size, 1, in_1, in_2, out_gen);

    t1  = test_function_bin_simd<T, simd::simd<T, 128, simd::nosimd_tag>, Func>(size, 1, in_1, in_2, out);
    v1  = test_equal(size, out, out_gen, 1.0, d1, check_nans);

    t3  = test_function_bin_simd<T, simd::simd<T, 128, simd::sse_tag>, Func>(size, 1, in_1, in_2, out);    
    v3  = test_equal(size, out, out_gen, 1.0, d3, check_nans);

    bool ok = v1 && v3;

    int N       = get_size_perf();
    int M       = get_num_rep();

    t0  = test_function_bin_simd<T, simd::simd<T, 128, simd::nosimd_tag>, Func>
                (N, M, in_1, in_2, out_gen);
    t1  = test_function_bin_simd<T, simd::simd<T, 128, simd::nosimd_tag>, Func>
                (N, M, in_1, in_2, out);
    t3  = test_function_bin_simd<T, simd::simd<T, 128, simd::sse_tag>, Func>
                (N, M, in_1, in_2, out);    

    std::string status  = (ok == true) ? "OK" : "FAIL"; 
    fd.disp_row(Func::name(), t0, t0/t1, t0/t3, status);
};

template<class T, class Func>
void test_simd::test_function_3(formatted_disp& fd, int size, const T* in_1, 
                               const T* in_2, const T* in_3, T* out, T* out_gen)
{
    double t0, t1, t2, t3, t4, t5;
    bool v1, v2, v3, v4, v5;
    double d1, d2, d3, d4, d5;

    t0  = test_function_3_simd<T, simd::simd<T, 128, simd::nosimd_tag>, Func>
                (size, 1, in_1, in_2, in_3, out_gen);

    t1  = test_function_3_simd<T, simd::simd<T, 128, simd::nosimd_tag>, Func>
                (size, 1, in_1, in_2, in_3, out);
    v1  = test_equal(size, out, out_gen, 1.0, d1, true);

    t2  = test_function_3_simd<T, simd::simd<T, 256, simd::nosimd_tag>, Func>
                (size, 1, in_1, in_2, in_3, out);
    v2  = test_equal(size, out, out_gen, 1.0, d2, true);

    t3  = test_function_3_simd<T, simd::simd<T, 128, simd::sse_tag>, Func>
                (size, 1, in_1, in_2, in_3, out);    
    v3  = test_equal(size, out, out_gen, 1.0, d3, true);

    t4  = test_function_3_simd<T, simd::simd<T, 256, simd::sse_tag>, Func>
                (size, 1, in_1, in_2, in_3, out);
    v4  = test_equal(size, out, out_gen, 1.0, d4, true);

    #if MATCL_ARCHITECTURE_HAS_AVX
        t5  = test_function_3_simd<T, simd::simd<T, 256, simd::avx_tag>, Func>
                    (size, 1, in_1, in_2, in_3, out);    
        v5  = test_equal(size, out, out_gen, 1.0, d5, true);
    #else
        t5  = t0;
        v5  = true;
        d5  = 0;
    #endif

    bool ok = v1 && v2 && v3 && v4 && v5;

    int N       = get_size_perf();
    int M       = get_num_rep();

    t0  = test_function_3_simd<T, simd::simd<T, 128, simd::nosimd_tag>, Func>
                (N, M, in_1, in_2, in_3, out_gen);
    t1  = test_function_3_simd<T, simd::simd<T, 128, simd::nosimd_tag>, Func>
                (N, M, in_1, in_2, in_3, out);
    t2  = test_function_3_simd<T, simd::simd<T, 256, simd::nosimd_tag>, Func>
                (N, M, in_1, in_2, in_3, out);
    t3  = test_function_3_simd<T, simd::simd<T, 128, simd::sse_tag>, Func>
                (N, M, in_1, in_2, in_3, out);    
    t4  = test_function_3_simd<T, simd::simd<T, 256, simd::sse_tag>, Func>
                (N, M, in_1, in_2, in_3, out);

    #if MATCL_ARCHITECTURE_HAS_AVX
        t5  = test_function_3_simd<T, simd::simd<T, 256, simd::avx_tag>, Func>
                (N, M, in_1, in_2, in_3, out);    
    #else
        t5  = t0;
    #endif

    std::string status  = (ok == true) ? "OK" : "FAIL"; 
    fd.disp_row(Func::name(), t0, t0/t1, t0/t2, t0/t3, t0/t4, t0/t5, status);
};

template<class T, class Func>
void test_simd::test_function_block(formatted_disp& fd, int size, const T* in, 
                                    T* out, T* out_gen, bool check_nans)
{
    double t0, t1, t2, t3, t4;
    bool v1, v3, v4;
    double d1, d3, d4;

    t0  = test_function_simd<T, simd::simd<T, 128, simd::nosimd_tag>, Func>(size, 1, in, out_gen);

    t1  = test_function_simd<T, simd::simd<T, 128, simd::sse_tag>, Func>(size, 1, in, out);    
    v1  = test_equal(size, out, out_gen, 4.0, d1, check_nans);

    t2  = test_function_simd<T, simd::simd<T, 256, simd::nosimd_tag>, Func>(size, 1, in, out_gen);

    t3  = test_function_simd<T, simd::simd<T, 256, simd::sse_tag>, Func>(size, 1, in, out);
    v3  = test_equal(size, out, out_gen, 4.0, d3, check_nans);

    #if MATCL_ARCHITECTURE_HAS_AVX
        t4  = test_function_simd<T, simd::simd<T, 256, simd::avx_tag>, Func>(size, 1, in, out);    
        v4  = test_equal(size, out, out_gen, 4.0, d4, check_nans);
    #else
        t4  = t0;
        v4  = true;
        d4  = 0;
    #endif

    bool ok = v1 && v3 && v4;

    int N       = get_size_perf();
    int M       = get_num_rep();

    t0  = test_function_simd<T, simd::simd<T, 128, simd::nosimd_tag>, Func>
                (N, M, in, out_gen);
    t1  = test_function_simd<T, simd::simd<T, 128, simd::sse_tag>, Func>
                (N, M, in, out);    
    t2  = test_function_simd<T, simd::simd<T, 256, simd::nosimd_tag>, Func>
                (N, M, in, out_gen);
    t3  = test_function_simd<T, simd::simd<T, 256, simd::sse_tag>, Func>
                (N, M, in, out);

    #if MATCL_ARCHITECTURE_HAS_AVX
        t4  = test_function_simd<T, simd::simd<T, 256, simd::avx_tag>, Func>
                (N, M, in, out);    
    #else
        t4  = t0;
    #endif

    std::string status  = (ok == true) ? "OK" : "FAIL"; 
    fd.disp_row(Func::name(), t0, t0/t0, t0/t2, t0/t1, t0/t3, t0/t4, status);
};

int test_simd::get_size() const
{
    #ifdef _DEBUG
        int N   = 1000;
    #else
        int N   = 10000;
    #endif

    if (m_test_values == true)
        #ifdef _DEBUG
            return 100000;
        #else
            return 1000000;
        #endif
    else
        return N;
};

int test_simd::get_size_perf() const
{
    return 1000;
}

int test_simd::get_num_rep() const
{
    #ifdef _DEBUG
        int M   = 1000;
    #else
        int M   = 100000;
    #endif

    if (m_test_values == true)
        return M/10;
    else
        return M;
}

template<class T>
void test_simd::test_functions()
{
    int N   = get_size();

    std::vector<T> in;
    std::vector<T> out;
    std::vector<T> out_gen;

    in.resize(N);
    out.resize(N);
    out_gen.resize(N);

    T* ptr_in       = in.data();
    T* ptr_out      = out.data();
    T* ptr_out_gen  = out_gen.data();

    for (int i = 0; i < N; ++i)
        ptr_in[i]   = rand_scalar<T>::make(m_test_values);

    std::string header  = m_instr_tag + " " + typeid(T).name();

    disp(" ");
    disp(header);

    formatted_disp dm;

    dm.set_row_label("func",    align_type::right, 10);
    dm.add_column("nosimd",     align_type::left, 5);
    dm.add_column("128 no",     align_type::left, 5);
    dm.add_column("256 no",     align_type::left, 5);
    dm.add_column("128 sse",    align_type::left, 5);
    dm.add_column("256 sse",    align_type::left, 5);
    dm.add_column("256 avx",    align_type::left, 5);
    dm.add_column("status",     align_type::left, 5);

    dm.disp_header();

    test_function<T, test_functions::Func_signbit_base>(dm, N, ptr_in, ptr_out, ptr_out_gen, true);
    test_function<T, test_functions::Func_abs>(dm, N, ptr_in, ptr_out, ptr_out_gen, true);
    test_function<T, test_functions::Func_round>(dm, N, ptr_in, ptr_out, ptr_out_gen, true);
    test_function<T, test_functions::Func_floor>(dm, N, ptr_in, ptr_out, ptr_out_gen, true);
    test_function<T, test_functions::Func_ceil>(dm, N, ptr_in, ptr_out, ptr_out_gen, true);
    test_function<T, test_functions::Func_trunc>(dm, N, ptr_in, ptr_out, ptr_out_gen, true);
    test_function<T, test_functions::Func_uminus>(dm, N, ptr_in, ptr_out, ptr_out_gen, true);
    test_function<T, test_functions::Func_bit_not>(dm, N, ptr_in, ptr_out, ptr_out_gen, true);

    test_function_block<T, test_functions::Func_cast_int32>(dm, N, ptr_in, ptr_out, ptr_out_gen, true); 
    test_function_block<T, test_functions::Func_cast_int64>(dm, N, ptr_in, ptr_out, ptr_out_gen, true); 
    test_function<T, test_functions::Func_cast>(dm, N, ptr_in, ptr_out, ptr_out_gen, true); 
    test_function<T, test_functions::Func_is_nan>(dm, N, ptr_in, ptr_out, ptr_out_gen, true);        
    test_function<T, test_functions::Func_is_finite>(dm, N, ptr_in, ptr_out, ptr_out_gen, true);        
    test_function<T, test_functions::Func_shift_left>(dm, N, ptr_in, ptr_out, ptr_out_gen, true); 
    test_function<T, test_functions::Func_shift_left2>(dm, N, ptr_in, ptr_out, ptr_out_gen, true); 
    test_function<T, test_functions::Func_shift_right>(dm, N, ptr_in, ptr_out, ptr_out_gen, true); 
    test_function<T, test_functions::Func_shift_right2>(dm, N, ptr_in, ptr_out, ptr_out_gen, true); 
    test_function<T, test_functions::Func_shift_right_a>(dm, N, ptr_in, ptr_out, ptr_out_gen, true);     
    test_function<T, test_functions::Func_shift_right_a2>(dm, N, ptr_in, ptr_out, ptr_out_gen, true);     

    test_function_block<T, test_functions::Func_extract_low>(dm, N, ptr_in, ptr_out, ptr_out_gen, true); 
    test_function_block<T, test_functions::Func_extract_high>(dm, N, ptr_in, ptr_out, ptr_out_gen, true); 
    test_function_block<T, test_functions::Func_any_nan>(dm, N, ptr_in, ptr_out, ptr_out_gen, true);
    test_function_block<T, test_functions::Func_any>(dm, N, ptr_in, ptr_out, ptr_out_gen, true);    
    test_function_block<T, test_functions::Func_all>(dm, N, ptr_in, ptr_out, ptr_out_gen, true);
    test_function_block<T, test_functions::Func_reverse>(dm, N, ptr_in, ptr_out, ptr_out_gen, true);    

    // block methods are not exact; use positive values in order to
    // reduce roundoff errors; scaling in order to avoid overflows
    for (int i = 0; i < N; ++i)
        ptr_in[i]   = std::abs(ptr_in[i]) / T(8);
    
    test_function_block<T, test_functions::Func_hor_sum>(dm, N, ptr_in, ptr_out, ptr_out_gen, true); 

    // nan not allowed
    for (int i = 0; i < N; ++i)
    {
        if (is_nan(ptr_in[i]) == true)
        ptr_in[i]   = T();
    }

    test_function_block<T, test_functions::Func_hor_min>(dm, N, ptr_in, ptr_out, ptr_out_gen, false); 
    test_function_block<T, test_functions::Func_hor_max>(dm, N, ptr_in, ptr_out, ptr_out_gen, false); 
};

template<class T>
void test_simd::test_functions_select()
{
    int N   = get_size();

    std::vector<T> in;
    std::vector<T> out;
    std::vector<T> out_gen;

    in.resize(N);
    out.resize(N);
    out_gen.resize(N);

    T* ptr_in       = in.data();
    T* ptr_out      = out.data();
    T* ptr_out_gen  = out_gen.data();

    for (int i = 0; i < N; ++i)
        ptr_in[i]   = rand_scalar<T>::make(m_test_values);

    std::string header  = m_instr_tag + " " + typeid(T).name();

    disp(" ");
    disp(header);

    formatted_disp dm;

    dm.set_row_label("func",    align_type::right, 10);
    dm.add_column("nosimd",     align_type::left, 5);
    dm.add_column("128 no",     align_type::left, 5);
    dm.add_column("256 no",     align_type::left, 5);
    dm.add_column("128 sse",    align_type::left, 5);
    dm.add_column("256 sse",    align_type::left, 5);
    dm.add_column("256 avx",    align_type::left, 5);
    dm.add_column("status",     align_type::left, 5);

    dm.disp_header();

    test_function_block<T, test_functions::Func_select_1>(dm, N, ptr_in, ptr_out, ptr_out_gen, true);
    test_function_block<T, test_functions::Func_select_2>(dm, N, ptr_in, ptr_out, ptr_out_gen, true);
    test_function_block<T, test_functions::Func_select_3>(dm, N, ptr_in, ptr_out, ptr_out_gen, true);
    test_function_block<T, test_functions::Func_select_4>(dm, N, ptr_in, ptr_out, ptr_out_gen, true);
    test_function_block<T, test_functions::Func_select_5>(dm, N, ptr_in, ptr_out, ptr_out_gen, true);
    test_function_block<T, test_functions::Func_select_6>(dm, N, ptr_in, ptr_out, ptr_out_gen, true);
    test_function_block<T, test_functions::Func_select_7>(dm, N, ptr_in, ptr_out, ptr_out_gen, true);
};

template<class T>
void test_simd::test_functions_math()
{
    int N   = get_size();

    std::vector<T> in;
    std::vector<T> out;
    std::vector<T> out_gen;

    in.resize(N);
    out.resize(N);
    out_gen.resize(N);

    T* ptr_in       = in.data();
    T* ptr_out      = out.data();
    T* ptr_out_gen  = out_gen.data();

    for (int i = 0; i < N; ++i)
        ptr_in[i]   = rand_scalar<T>::make(m_test_values);

    std::string header  = m_instr_tag + " " + typeid(T).name();

    disp(" ");
    disp(header);

    formatted_disp dm;

    dm.set_row_label("func",    align_type::right, 10);
    dm.add_column("base",       align_type::left, 5);
    dm.add_column("128 no",     align_type::left, 5);
    dm.add_column("256 no",     align_type::left, 5);
    dm.add_column("128 sse",    align_type::left, 5);
    dm.add_column("256 sse",    align_type::left, 5);
    dm.add_column("256 avx",    align_type::left, 5);
    dm.add_column("status",     align_type::left, 5);

    dm.disp_header();

    test_function_math<T, test_functions::Func_tan>(dm, N, ptr_in, ptr_out, ptr_out_gen, true);
    test_function_math<T, test_functions::Func_cot>(dm, N, ptr_in, ptr_out, ptr_out_gen, true);
    test_function_math<T, test_functions::Func_exp>(dm, N, ptr_in, ptr_out, ptr_out_gen, true);     
    test_function_math<T, test_functions::Func_sin>(dm, N, ptr_in, ptr_out, ptr_out_gen, true);
    test_function_math<T, test_functions::Func_cos>(dm, N, ptr_in, ptr_out, ptr_out_gen, true);
    test_function<T, test_functions::Func_fraction>(dm, N, ptr_in, ptr_out, ptr_out_gen, true); 
    test_function<T, test_functions::Func_iexponent>(dm, N, ptr_in, ptr_out, ptr_out_gen, true); 
    test_function<T, test_functions::Func_exponent>(dm, N, ptr_in, ptr_out, ptr_out_gen, true); 
    
    for (int i = 0; i < N; ++i)
        ptr_in[i]   = std::abs(ptr_in[i]);
    
    test_function<T, test_functions::Func_sqrt>(dm, N, ptr_in, ptr_out, ptr_out_gen, true);
    test_function_math<T, test_functions::Func_log>(dm, N, ptr_in, ptr_out, ptr_out_gen, true); 
};

template<class T>
void test_simd::test_functions_int()
{
    int N           = get_size();
    int max_int     = 32;

    std::vector<int32_t> in_32;
    std::vector<int64_t> in_64;
    std::vector<T> in_t;
    std::vector<T> out;
    std::vector<T> out_gen;
    std::vector<T> arg;

    in_32.resize(N);
    in_64.resize(N);
    in_t.resize(N);
    out.resize(N);
    out_gen.resize(N);
    arg.resize(2*max_int + 1);

    int32_t* ptr_in_32  = in_32.data();
    int64_t* ptr_in_64  = in_64.data();
    T* ptr_in_t         = in_t.data();

    T* ptr_out      = out.data();
    T* ptr_out_gen  = out_gen.data();    
    T* arg_ptr      = arg.data();

    for (int i = 0; i < N; ++i)
        ptr_in_32[i]   = rand_scalar<int32_t>::make(m_test_values) % max_int;

    for (int i = 0; i < N; ++i)
        ptr_in_64[i]   = rand_scalar<int64_t>::make(m_test_values) % max_int;

    for (int i = 0; i < N; ++i)
        ptr_in_t[i]   = T(rand_scalar<int32_t>::make(m_test_values) % max_int);

    for (int i = 0; i < max_int*2 + 1; ++i)
        arg_ptr[i]  = rand_scalar<T>::make(false);

    arg_ptr         = arg_ptr + max_int;

    std::string header  = m_instr_tag + " " + typeid(T).name();

    disp(" ");
    disp(header);

    formatted_disp dm;

    dm.set_row_label("func",    align_type::right, 10);
    dm.add_column("nosimd",     align_type::left, 5);
    dm.add_column("128 no",     align_type::left, 5);
    dm.add_column("256 no",     align_type::left, 5);
    dm.add_column("128 sse",    align_type::left, 5);
    dm.add_column("256 sse",    align_type::left, 5);
    dm.add_column("256 avx",    align_type::left, 5);
    dm.add_column("status",     align_type::left, 5);

    dm.disp_header();

    test_function_int<T, int32_t, test_functions::Func_gather_int32<T>>(dm, N, ptr_in_32, ptr_out, ptr_out_gen,
                                                test_functions::Func_gather_int32<T>(arg_ptr));
    test_function_int<T, int64_t, test_functions::Func_gather_int64<T>>(dm, N, ptr_in_64, ptr_out, ptr_out_gen,
                                                test_functions::Func_gather_int64<T>(arg_ptr));
    test_function_int<T, int32_t, test_functions::Func_pow2ki_int32<T>>(dm, N, ptr_in_32, ptr_out, ptr_out_gen,
                                                test_functions::Func_pow2ki_int32<T>());
    test_function_int<T, int64_t, test_functions::Func_pow2ki_int64<T>>(dm, N, ptr_in_64, ptr_out, ptr_out_gen,
                                                test_functions::Func_pow2ki_int64<T>());
    test_function_int<T, T, test_functions::Func_pow2k>(dm, N, ptr_in_t, ptr_out, ptr_out_gen,
                                                test_functions::Func_pow2k());
};

template<class T>
void test_simd::test_functions_bin()
{
    int N   = get_size();

    std::vector<T> in_1;
    std::vector<T> in_2;
    std::vector<T> out;
    std::vector<T> out_gen;

    in_1.resize(N);
    in_2.resize(N);
    out.resize(N);
    out_gen.resize(N);

    T* ptr_in_1     = in_1.data();
    T* ptr_in_2     = in_2.data();
    T* ptr_out      = out.data();
    T* ptr_out_gen  = out_gen.data();

    for (int i = 0; i < N; ++i)
    {
        ptr_in_1[i] = rand_scalar<T>::make(m_test_values);
        ptr_in_2[i] = rand_scalar<T>::make(m_test_values);
    };

    std::string header  = m_instr_tag + " " + typeid(T).name();

    disp(" ");
    disp(header);

    formatted_disp dm;

    dm.set_row_label("func",    align_type::right, 9);
    dm.add_column("nosimd",     align_type::left, 5);
    dm.add_column("128 no",     align_type::left, 5);
    dm.add_column("256 no",     align_type::left, 5);
    dm.add_column("128 sse",    align_type::left, 5);
    dm.add_column("256 sse",    align_type::left, 5);
    dm.add_column("256 avx",    align_type::left, 5);
    dm.add_column("status",     align_type::left, 5);

    dm.disp_header();

    test_function_bin<T, test_functions::Func_leq>(dm, N, ptr_in_1, ptr_in_2, ptr_out, ptr_out_gen);
    test_function_bin<T, test_functions::Func_geq>(dm, N, ptr_in_1, ptr_in_2, ptr_out, ptr_out_gen);
    test_function_bin<T, test_functions::Func_lt>(dm, N, ptr_in_1, ptr_in_2, ptr_out, ptr_out_gen);
    test_function_bin<T, test_functions::Func_gt>(dm, N, ptr_in_1, ptr_in_2, ptr_out, ptr_out_gen);

    test_function_bin<T, test_functions::Func_sub_add>(dm, N, ptr_in_1, ptr_in_2, ptr_out, ptr_out_gen);
    test_function_bin<T, test_functions::Func_mult>(dm, N, ptr_in_1, ptr_in_2, ptr_out, ptr_out_gen);
    test_function_bin<T, test_functions::Func_div>(dm, N, ptr_in_1, ptr_in_2, ptr_out, ptr_out_gen);
    test_function_bin<T, test_functions::Func_plus>(dm, N, ptr_in_1, ptr_in_2, ptr_out, ptr_out_gen);    
    test_function_bin<T, test_functions::Func_minus>(dm, N, ptr_in_1, ptr_in_2, ptr_out, ptr_out_gen);    
    test_function_bin<T, test_functions::Func_max>(dm, N, ptr_in_1, ptr_in_2, ptr_out, ptr_out_gen);
    test_function_bin<T, test_functions::Func_min>(dm, N, ptr_in_1, ptr_in_2, ptr_out, ptr_out_gen);

    test_function_bin<T, test_functions::Func_bit_and>(dm, N, ptr_in_1, ptr_in_2, ptr_out, ptr_out_gen);
    test_function_bin<T, test_functions::Func_bit_or>(dm, N, ptr_in_1, ptr_in_2, ptr_out, ptr_out_gen);
    test_function_bin<T, test_functions::Func_bit_xor>(dm, N, ptr_in_1, ptr_in_2, ptr_out, ptr_out_gen);
    test_function_bin<T, test_functions::Func_bit_andnot>(dm, N, ptr_in_1, ptr_in_2, ptr_out, ptr_out_gen);

    test_function_bin<T, test_functions::Func_if_zero_else>(dm, N, ptr_in_1, ptr_in_2, ptr_out, ptr_out_gen);
    test_function_bin<T, test_functions::Func_if_nan_else>(dm, N, ptr_in_1, ptr_in_2, ptr_out, ptr_out_gen);

    for (int i = 0; i < N; i += 3)
    {
        ptr_in_2[i] = ptr_in_1[i];
    };

    test_function_bin<T, test_functions::Func_eeq>(dm, N, ptr_in_1, ptr_in_2, ptr_out, ptr_out_gen);
    test_function_bin<T, test_functions::Func_neq>(dm, N, ptr_in_1, ptr_in_2, ptr_out, ptr_out_gen);
};

template<class T>
void test_simd::test_functions_combine()
{
    int N   = get_size();

    std::vector<T> in_1;
    std::vector<T> in_2;
    std::vector<T> out;
    std::vector<T> out_gen;

    in_1.resize(N);
    in_2.resize(N);
    out.resize(N);
    out_gen.resize(N);

    T* ptr_in_1     = in_1.data();
    T* ptr_in_2     = in_2.data();
    T* ptr_out      = out.data();
    T* ptr_out_gen  = out_gen.data();

    for (int i = 0; i < N; ++i)
    {
        ptr_in_1[i] = rand_scalar<T>::make(m_test_values);
        ptr_in_2[i] = rand_scalar<T>::make(m_test_values);
    };

    std::string header  = m_instr_tag + " " + typeid(T).name();

    disp(" ");
    disp(header);

    formatted_disp dm;

    dm.set_row_label("func",    align_type::right, 9);
    dm.add_column("nosimd",     align_type::left, 5);
    dm.add_column("128 no",     align_type::left, 5);
    dm.add_column("128 sse",    align_type::left, 5);
    dm.add_column("status",     align_type::left, 5);

    dm.disp_header();

    test_function_combine<T, test_functions::Func_combine_1>(dm, N, ptr_in_1, ptr_in_2, ptr_out, ptr_out_gen, true);
    test_function_combine<T, test_functions::Func_combine_2>(dm, N, ptr_in_1, ptr_in_2, ptr_out, ptr_out_gen, true);
    test_function_combine<T, test_functions::Func_combine_3>(dm, N, ptr_in_1, ptr_in_2, ptr_out, ptr_out_gen, true);
    test_function_combine<T, test_functions::Func_combine_4>(dm, N, ptr_in_1, ptr_in_2, ptr_out, ptr_out_gen, true);
    test_function_combine<T, test_functions::Func_combine_5>(dm, N, ptr_in_1, ptr_in_2, ptr_out, ptr_out_gen, true);
    test_function_combine<T, test_functions::Func_combine_6>(dm, N, ptr_in_1, ptr_in_2, ptr_out, ptr_out_gen, true);
    test_function_combine<T, test_functions::Func_combine_7>(dm, N, ptr_in_1, ptr_in_2, ptr_out, ptr_out_gen, true);
    test_function_combine<T, test_functions::Func_combine_8>(dm, N, ptr_in_1, ptr_in_2, ptr_out, ptr_out_gen, true);
    test_function_combine<T, test_functions::Func_combine_9>(dm, N, ptr_in_1, ptr_in_2, ptr_out, ptr_out_gen, true);
    test_function_combine<T, test_functions::Func_combine_10>(dm, N, ptr_in_1, ptr_in_2, ptr_out, ptr_out_gen, true);
    test_function_combine<T, test_functions::Func_combine_11>(dm, N, ptr_in_1, ptr_in_2, ptr_out, ptr_out_gen, true);
};

template<class T>
void test_simd::test_functions_3()
{
    int N   = get_size();

    std::vector<T> in_1;
    std::vector<T> in_2;
    std::vector<T> in_3;
    std::vector<T> out;
    std::vector<T> out_gen;

    in_1.resize(N);
    in_2.resize(N);
    in_3.resize(N);
    out.resize(N);
    out_gen.resize(N);

    T* ptr_in_1     = in_1.data();
    T* ptr_in_2     = in_2.data();
    T* ptr_in_3     = in_3.data();
    T* ptr_out      = out.data();
    T* ptr_out_gen  = out_gen.data();

    std::string header  = m_instr_tag + " " + typeid(T).name();

    disp(" ");
    disp(header);

    formatted_disp dm;

    dm.set_row_label("func",    align_type::right, 7);
    dm.add_column("nosimd",     align_type::left, 5);
    dm.add_column("128 no",     align_type::left, 5);
    dm.add_column("256 no",     align_type::left, 5);
    dm.add_column("128 sse",    align_type::left, 5);
    dm.add_column("256 sse",    align_type::left, 5);
    dm.add_column("256 avx",    align_type::left, 5);
    dm.add_column("status",     align_type::left, 5);

    dm.disp_header();

    test_function_3<T, test_functions::Func_if_then_else>(dm, N, ptr_in_1, ptr_in_2, 
                                                 ptr_in_3, ptr_out, ptr_out_gen);

    for (int i = 0; i < N; ++i)
    {
        // avoid large round-off errors
        ptr_in_1[i] = std::abs(rand_scalar<T>::make(m_test_values));
        ptr_in_2[i] = std::abs(rand_scalar<T>::make(m_test_values));
        ptr_in_3[i] = std::abs(rand_scalar<T>::make(m_test_values));
    };

    test_function_3<T, test_functions::Func_fma_a>(dm, N, ptr_in_1, ptr_in_2, 
                                                 ptr_in_3, ptr_out, ptr_out_gen);
    test_function_3<T, test_functions::Func_fma_f>(dm, N, ptr_in_1, ptr_in_2, 
                                                 ptr_in_3, ptr_out, ptr_out_gen);

    for (int i = 0; i < N; ++i)
    {
        // avoid large round-off errors
        ptr_in_3[i] = -ptr_in_3[i];
    };

    test_function_3<T, test_functions::Func_fms_f>(dm, N, ptr_in_1, ptr_in_2, 
                                                 ptr_in_3, ptr_out, ptr_out_gen);
    test_function_3<T, test_functions::Func_fms_a>(dm, N, ptr_in_1, ptr_in_2, 
                                                 ptr_in_3, ptr_out, ptr_out_gen);

    test_function_3<T, test_functions::Func_fnma_a>(dm, N, ptr_in_1, ptr_in_2, 
                                                 ptr_in_3, ptr_out, ptr_out_gen);
    test_function_3<T, test_functions::Func_fnma_f>(dm, N, ptr_in_1, ptr_in_2, 
                                                 ptr_in_3, ptr_out, ptr_out_gen);

    for (int i = 0; i < N; ++i)
    {
        // avoid large round-off errors
        ptr_in_3[i] = -ptr_in_3[i];
    };

    test_function_3<T, test_functions::Func_fnms_f>(dm, N, ptr_in_1, ptr_in_2, 
                                                 ptr_in_3, ptr_out, ptr_out_gen);
    test_function_3<T, test_functions::Func_fnms_a>(dm, N, ptr_in_1, ptr_in_2, 
                                                 ptr_in_3, ptr_out, ptr_out_gen);
};

}};
