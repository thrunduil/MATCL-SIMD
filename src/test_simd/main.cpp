/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#include "test_simd_config.h"
#include "test_simd.h"
#include "test_simd_int.h"
#include "test_simd_scalar.h"
#include "test_simd_scalar_int.h"
#include "test_simd_compl.h"

#include <iostream>
#include <fstream>

using namespace matcl;

int main(int argc, const char* argv[])
{
    (void)argc;
    (void)argv;

    using log_ptr   = std::shared_ptr<std::ofstream>;

    try
    {         
        {
            std::string log_file_name   = std::string("log_test_simd_") + MATCL_TEST_SIMD_TAG + ".txt";
            log_ptr log = log_ptr(new std::ofstream(log_file_name));
            //set_logger(log);
        };               
        
        matcl::test::test_performance_real();
        matcl::test::test_performance_int();

        matcl::test::test_performance_real_scalar(); 
        matcl::test::test_performance_int_scalar();                      

        matcl::test::test_performance_complex();  

        std::cout << "\n";
        std::cout << "finished" << "\n";
    }
    catch(std::exception& ex)
    {
        std::cout << ex.what() << "\n";
        return 1;
    };

    return 0;
}
