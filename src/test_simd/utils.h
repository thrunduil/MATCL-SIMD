/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "test_simd_config.h"
#include "matcl-simd/complex/scalar_types.h"
#include <complex>

namespace matcl { namespace test
{

bool eeq_nan(const Float& x, const Float& y);
bool eeq_nan(const Real& x, const Real& y);
bool eeq_nan(const Float_complex& x, const Float_complex& y);
bool eeq_nan(const Complex& x, const Complex& y);

Integer   abs(const Integer& x);
Float   abs(const Float& x);
Real    abs(const Real& x);
Float   abs(const Float_complex& x);
Real    abs(const Complex& x);

bool    is_nan(const Float& x);
bool    is_nan(const Real& x);

Float   eps(const Float& x);
Real    eps(const Real& x);

Float   float_distance(const Float& x, const Float& y);
Real    float_distance(const Real& x, const Real& y);

template<class T>
struct rand_scalar;

template<>
struct rand_scalar<float>
{
    static float    make(bool testing_values);
    static float    make_special();
    static float    rand_scale();
};

template<>
struct rand_scalar<double>
{
    static double   make(bool testing_values);
    static double   make_special();
    static double   rand_scale();
};

template<>
struct rand_scalar<int32_t>
{
    static int32_t  make(bool testing_values);
    //static int32_t  make_special();
    //static int32_t  rand_scale();
};

template<>
struct rand_scalar<int64_t>
{
    static int64_t  make(bool testing_values);
    //static int64_t  make_special();
    //static int64_t  rand_scale();
};

template<>
struct rand_scalar<Float_complex>
{
    static Float_complex    make(bool testing_values);
    static Float_complex    make_special();
};

template<>
struct rand_scalar<Complex>
{
    static Complex  make(bool testing_values);
    static Complex  make_special();
};

void disp(const std::string& str);

// determine how strings are aligned
enum class align_type : int
{
    left,           // justify text to left
    center,         // justify text to center
    right           // justify text to right
};

// format of a column
class column_info
{
    private:
        std::string         m_name;
        align_type          m_align;
        int                 m_width;

    public:
        // create uninitialized object
        column_info();

        // define column name, alignment type and preferred width 
        // in given column
        column_info(const std::string& name, align_type align, int width);

    public:
        // return column name
        const std::string&  name() const;

        // return alignment type
        align_type          align() const;

        // return preferred column width
        int                 width() const;
};

class formatted_disp
{
    public:
        formatted_disp();

    public:
        // set format of row labels; if not set, then row labels are not printed
        void                set_row_label(const std::string& name, align_type al,
                                int width);
        void                set_row_label(const column_info& format);

        // set format of next column
        void                add_column(const std::string& name, align_type al,
                                int width);
        void                add_column(const column_info& format);

        // display column header
        void                disp_header();

        // display next row; row label 'label' is displayed, when set_row_label
        // function is called, otherwise is ignored; number of remaining arguments
        // must be equal to number of columns
        template<class ... Args>
        void                disp_row(const std::string& label, Args&& ... args);

        // display next row; row label 'label' is displayed, when set_row_label
        // function is called, otherwise is ignored; number of remaining arguments
        // must be equal to number of columns; values associated with colums are
        // stored in argument row of type formatted_disp_row object; at the end
        // row.clear() is called
        //void                disp_row(const std::string& label, formatted_disp_row& row);

    public:
        // return true if row labels will be displayed
        bool                display_row_label() const;

        // return number of columns to be displayed
        Integer             number_columns() const;

        // return format of column 'col'
        const column_info&  get_column_format(Integer col) const;

        // return format of row labels
        const column_info&  get_row_label_format() const;
};

template<class ... Args>
void formatted_disp::disp_row(const std::string&, Args&& ...)
{}

// start timer
void    tic();

// get elapsed time in seconds; result is not reported
double  toc();

}};

