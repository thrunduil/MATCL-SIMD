/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#include "test_simd_config.h"
#include "utils.h"

#include "matcl-simd/simd.h"
#include "matcl-simd/complex/complex_details.h"

namespace matcl { namespace test
{

Float frandn()
{
    return Float(0.0f);
}

Float frand()
{
    return Float(0.0f);
}

Integer irand()
{
    return 0;
}

Real randn()
{
    return 0.0;
}

Complex crandn()
{
    return Complex();
}

Float_complex fcrandn()
{
    return Float_complex();
}

float rand_scalar<float>::make(bool testing_values)
{
    if (testing_values)
        return make_special();
    else
        return 10.0f * frandn();
};

float rand_scalar<float>::make_special()
{
    int max_code    = 27;
    int code        = std::abs(irand()) % max_code;

    switch(code)
    {
        case 0: return 0.0f;
        case 1: return -0.0f;
        case 2: return 1.0f;
        case 3: return -1.0f;
        case 4: return 0.5f;
        case 5: return -0.5f;
        case 6: return 2.0f;
        case 7: return -2.0f;
        case 8: return -std::numeric_limits<float>::infinity();
        case 9: return std::numeric_limits<float>::infinity();
        case 10: return -std::numeric_limits<float>::quiet_NaN();
        case 11: return std::numeric_limits<float>::quiet_NaN();
        case 12: return -std::numeric_limits<float>::max();
        case 13: return std::numeric_limits<float>::max();
        case 14: return -std::numeric_limits<float>::min();
        case 15: return std::numeric_limits<float>::min();
        case 16: return 1.5f;
        case 17: return -1.5f;
        default:
            return frand() * rand_scale();
    };
};

float rand_scalar<float>::rand_scale()
{
    int max_exp     = std::numeric_limits<float>::max_exponent;
    int min_exp     = std::numeric_limits<float>::min_exponent;

    int num_pow     = max_exp - min_exp + 1;
    unsigned ir     = abs(irand());
    int pow         = min_exp + (ir % num_pow);

    float sign      = 1.0f;
    if (rand() < 0.5)
        sign        = -1.0f;

    float val       = sign * std::ldexp(1.0f, pow);
    return val;
};

int32_t rand_scalar<int32_t>::make(bool testing_values)
{
    (void)testing_values;
    return irand();
};

double rand_scalar<double>::make(bool testing_values)
{
    if (testing_values)
        return make_special();
    else
        return 10.0 * randn();
};

double rand_scalar<double>::make_special()
{
    int max_code    = 27;
    int code        = std::abs(irand()) % max_code;

    switch(code)
    {
        case 0: return 0.0;
        case 1: return -0.0;
        case 2: return 1.0;
        case 3: return -1.0;
        case 4: return 0.5;
        case 5: return -0.5;
        case 6: return 2.0;
        case 7: return -2.0;
        case 8: return -std::numeric_limits<double>::infinity();
        case 9: return std::numeric_limits<double>::infinity();
        case 10: return -std::numeric_limits<double>::quiet_NaN();
        case 11: return std::numeric_limits<double>::quiet_NaN();
        case 12: return -std::numeric_limits<double>::max();
        case 13: return std::numeric_limits<double>::max();
        case 14: return -std::numeric_limits<double>::min();
        case 15: return std::numeric_limits<double>::min();
        case 16: return 1.5;
        case 17: return -1.5;

        default:
            return rand() * rand_scale();
    };
};

double rand_scalar<double>::rand_scale()
{
    int max_exp = std::numeric_limits<double>::max_exponent;
    int min_exp = std::numeric_limits<double>::min_exponent;

    const int num_pow    = max_exp - min_exp + 1;

    // rand power
    unsigned ir     = abs(irand());
    int pow         = min_exp + (ir % num_pow);

    double sign     = 1.0;
    if (rand() < 0.5)
        sign        = -1.0;

    double val      = sign * std::ldexp(1.0, pow);
    return val;
};

int64_t rand_scalar<int64_t>::make(bool testing_values)
{
    (void)testing_values;
    return int64_t(irand()) * int64_t(irand());    
};

Complex rand_scalar<Complex>::make(bool testing_values)
{
    if (testing_values)
        return make_special();
    else
        return 10.0 * crandn();
};

Complex rand_scalar<Complex>::make_special()
{
    return Complex(rand_scalar<double>::make_special(), rand_scalar<double>::make_special());
};

Float_complex rand_scalar<Float_complex>::make(bool testing_values)
{
    if (testing_values)
        return make_special();
    else
        return 10.0f * fcrandn();
};

Float_complex rand_scalar<Float_complex>::make_special()
{
    return Float_complex(rand_scalar<float>::make_special(), rand_scalar<float>::make_special());
};

//-----------------------------------------------------------------------
//                  TODO: take implementations from matcl
//-----------------------------------------------------------------------
bool test::eeq_nan(const Float& x, const Float& y)
{
    return x == y;
}

bool test::eeq_nan(const Real& x, const Real& y)
{
    return x == y;
}

bool test::eeq_nan(const Float_complex& x, const Float_complex& y)
{
    return x == y;
}

bool test::eeq_nan(const Complex& x, const Complex& y)
{
    return x == y;
}

Integer test::abs(const Integer& x)
{
    return std::abs(x);
}
Float   test::abs(const Float& x)
{
    return std::abs(x);
}
Real    test::abs(const Real& x)
{
    return std::abs(x);
}
Float   test::abs(const Float_complex& x)
{
    return std::abs(real(x));
}
Real    test::abs(const Complex& x)
{
    return std::abs(real(x));
}

bool    test::is_nan(const Float& x)
{
    (void)x;
    return false;
}
bool    test::is_nan(const Real& x)
{
    (void)x;
    return false;
}

Float   test::eps(const Float& x)
{
    return x;
}
Real test::eps(const Real& x)
{
    return x;
}

Float test::float_distance(const Float& x, const Float& y)
{
    return x - y;
}
Real test::float_distance(const Real& x, const Real& y)
{
    return x - y;
}

void test::disp(const std::string& str)
{
    (void)str;
}

column_info::column_info()
    :m_align(align_type::center),m_width(10)
{};

column_info::column_info(const std::string& name, align_type align, int width)
    :m_name(name), m_align(align), m_width(width)
{};

const std::string& column_info::name() const
{
    return m_name;
}

align_type column_info::align() const
{
    return m_align;
}

int column_info::width() const
{
    return m_width;
}

formatted_disp::formatted_disp()
{}

void formatted_disp::set_row_label(const std::string&, align_type, int)
{}

void formatted_disp::set_row_label(const column_info&)
{};

void formatted_disp::add_column(const std::string&, align_type, int)
{};

void formatted_disp::add_column(const column_info&)
{}

void formatted_disp::disp_header()
{}

bool formatted_disp::display_row_label() const
{
    return false;
}

Integer formatted_disp::number_columns() const
{
    return 0;
};

column_info ci;

const column_info& formatted_disp::get_column_format(Integer) const
{
    return ci;
};

const column_info& formatted_disp::get_row_label_format() const
{
    return ci;
};

void test::tic()
{};

double test::toc()
{
    return 0.0;
}

}};
