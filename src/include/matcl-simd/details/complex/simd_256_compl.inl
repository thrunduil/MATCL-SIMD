/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/complex/simd_256_compl.h"

namespace matcl { namespace simd
{

//-------------------------------------------------------------------
//                          AVX DOUBLE COMPLEX
//-------------------------------------------------------------------
template<class Simd_tag>
force_inline
simd_compl<double, 256, Simd_tag>::simd_compl(const impl_type& v)
    : data(v) 
{};

template<class Simd_tag>
force_inline
simd_compl<double, 256, Simd_tag>::simd_compl(int32_t re)
    :simd_compl(double(re))
{};

template<class Simd_tag>
force_inline
simd_compl<double, 256, Simd_tag>::simd_compl(int64_t re)
    :simd_compl(double(re))
{};

template<class Simd_tag>
force_inline
simd_compl<double, 256, Simd_tag>::simd_compl(float re)
    :simd_compl(double(re))
{};

template<class Simd_tag>
force_inline
simd_compl<double, 256, Simd_tag>::simd_compl(double re)
    :simd_compl(simd_half(re))
{};

template<class Simd_tag>
force_inline
simd_compl<double, 256, Simd_tag>::simd_compl(const simd_half& lo_hi)
    : data(lo_hi.data)
{}

template<class Simd_tag>
force_inline
simd_compl<double, 256, Simd_tag>::simd_compl(const simd_half& lo, const simd_half& hi)
    : data(lo.data, hi.data)
{};

template<class Simd_tag>
force_inline
simd_compl<double, 256, Simd_tag>::simd_compl(double re, double im)
    :simd_compl(simd_half(re, im))
{};

template<class Simd_tag>
force_inline
simd_compl<double, 256, Simd_tag>::simd_compl(const simd_double_complex& val)
    :simd_compl(simd_half(val))
{};

template<class Simd_tag>
force_inline
simd_compl<double, 256, Simd_tag>::simd_compl(const simd_single_complex& val)
    :simd_compl(simd_half(val))
{};

template<class Simd_tag>
force_inline
simd_compl<double, 256, Simd_tag>::simd_compl(const simd_double_complex& v0, const simd_double_complex& v1)
    : simd_compl(simd_half(v0), simd_half(v1))
{};

template<class Simd_tag>
force_inline
simd_compl<double, 256, Simd_tag>::simd_compl(double re_0, double im_0, double re_1, double im_1)
    : data(re_0, im_0, re_1, im_1)
{};

template<class Simd_tag>
template<class Tag>
force_inline
simd_compl<double, 256, Simd_tag>::simd_compl(const simd_compl<double, 256, Tag>& s)
    : data(s.data)
{}

template<class Simd_tag>
force_inline
simd_compl<double, 256, Simd_tag> simd_compl<double, 256, Simd_tag>::zero()
{
    return impl_type::zero();
}

template<class Simd_tag>
force_inline simd_compl<double, 256, Simd_tag> 
simd_compl<double, 256, Simd_tag>::broadcast(const simd_double_complex* arr)
{
    return simd_compl(arr[0]);
}

template<class Simd_tag>
force_inline simd_compl<double, 256, Simd_tag> 
simd_compl<double, 256, Simd_tag>::broadcast(const simd_double_complex& arr)
{
    return simd_compl(arr);
}

template<class Simd_tag>
force_inline simd_compl<double, 256, Simd_tag>
simd_compl<double, 256, Simd_tag>::broadcast(const double* arr)
{
    return simd_compl(arr[0]);
}

template<class Simd_tag>
force_inline simd_compl<double, 256, Simd_tag>
simd_compl<double, 256, Simd_tag>::broadcast(const double& arr)
{
    return simd_compl(arr);
}

template<class Simd_tag>
force_inline simd_compl<double, 256, Simd_tag> 
simd_compl<double, 256, Simd_tag>::load(const simd_double_complex* arr, std::true_type aligned)
{
    return impl_type::load((const double*)arr, aligned);
};

template<class Simd_tag>
force_inline simd_compl<double, 256, Simd_tag> 
simd_compl<double, 256, Simd_tag>::load(const simd_double_complex* arr, std::false_type not_aligned)
{
    return impl_type::load((const double*)arr, not_aligned);
};

template<class Simd_tag>
force_inline void 
simd_compl<double, 256, Simd_tag>::store(simd_double_complex* arr, std::true_type aligned) const
{
    data.store((double*)arr, aligned);
};

template<class Simd_tag>
force_inline void 
simd_compl<double, 256, Simd_tag>::store(simd_double_complex* arr, std::false_type not_aligned) const
{
    data.store((double*)arr, not_aligned);
};

template<class Simd_tag>
force_inline
simd_double_complex simd_compl<double, 256, Simd_tag>::get(int pos) const
{
    const simd_double_complex* ptr  = this->get_raw_ptr();
    return simd_double_complex(ptr[pos]);
};

template<class Simd_tag>
force_inline
simd_double_complex simd_compl<double, 256, Simd_tag>::first() const
{
    return simd_double_complex(get_raw_ptr()[0]);
};

template<class Simd_tag>
force_inline
void simd_compl<double, 256, Simd_tag>::set(int pos, const simd_double_complex& val)
{
    simd_double_complex* ptr    = this->get_raw_ptr();
    ptr[pos]                    = val;
};

template<class Simd_tag>
force_inline
const simd_double_complex*
simd_compl<double, 256, Simd_tag>::get_raw_ptr() const
{
    return reinterpret_cast<const simd_double_complex*>(data.get_raw_ptr());
}

template<class Simd_tag>
force_inline
simd_double_complex*
simd_compl<double, 256, Simd_tag>::get_raw_ptr()
{
    return reinterpret_cast<simd_double_complex*>(data.get_raw_ptr());
}

template<class Simd_tag>
force_inline
typename simd_compl<double, 256, Simd_tag>::simd_float
simd_compl<double, 256, Simd_tag>::convert_to_float() const
{
    return data.convert_to_float();
}

template<class Simd_tag>
template<int Step>
force_inline
void simd_compl<double, 256, Simd_tag>::scatter(simd_double_complex* arr0) const
{
    //no scatter intrinsic
    double* arr         = (double*) arr0;
    const double* ptr   = data.get_raw_ptr();

    arr[0*Step*2]       = ptr[0];
    arr[0*Step*2+1]     = ptr[1];
    arr[1*Step*2]       = ptr[2];
    arr[1*Step*2+1]     = ptr[3];
};

template<class Simd_tag>
force_inline typename simd_compl<double, 256, Simd_tag>::simd_half
simd_compl<double, 256, Simd_tag>::extract_low() const
{
    return data.extract_low();
}

template<class Simd_tag>
force_inline typename simd_compl<double, 256, Simd_tag>::simd_half 
simd_compl<double, 256, Simd_tag>::extract_high() const
{
    return data.extract_high();
}

template<class Simd_tag>
force_inline simd_compl<double, 256, Simd_tag>& 
simd_compl<double, 256, Simd_tag>::operator+=(const simd_compl& x)
{
    *this = *this + x;
    return *this;
}

template<class Simd_tag>
force_inline simd_compl<double, 256, Simd_tag>& 
simd_compl<double, 256, Simd_tag>::operator-=(const simd_compl& x)
{
    *this = *this - x;
    return *this;
}

template<class Simd_tag>
force_inline simd_compl<double, 256, Simd_tag>& 
simd_compl<double, 256, Simd_tag>::operator*=(const simd_compl& x)
{
    *this = *this * x;
    return *this;
}

template<class Simd_tag>
force_inline simd_compl<double, 256, Simd_tag>& 
simd_compl<double, 256, Simd_tag>::operator/=(const simd_compl& x)
{
    *this = *this / x;
    return *this;
}

//-------------------------------------------------------------------
//                          FLOAT COMPLEX
//-------------------------------------------------------------------
template<class Simd_tag>
force_inline
simd_compl<float, 256, Simd_tag>::simd_compl(const impl_type& v)  
    : data(v) 
{};

template<class Simd_tag>
force_inline
simd_compl<float, 256, Simd_tag>::simd_compl(float re)
    :simd_compl(simd_half(re))
{}

template<class Simd_tag>
force_inline
simd_compl<float, 256, Simd_tag>::simd_compl(const simd_half& lo_hi)
    : data(lo_hi.data)
{}

template<class Simd_tag>
force_inline
simd_compl<float, 256, Simd_tag>::simd_compl(const simd_half& lo, const simd_half& hi)
    : data(lo.data, hi.data)
{}

template<class Simd_tag>
force_inline
simd_compl<float, 256, Simd_tag>::simd_compl(float re, float im)
    : simd_compl(simd_half(re, im))
{}

template<class Simd_tag>
force_inline
simd_compl<float, 256, Simd_tag>::simd_compl(const simd_single_complex& val)
    : simd_compl(simd_half(val))
{}

template<class Simd_tag>
force_inline
simd_compl<float, 256, Simd_tag>::simd_compl(const simd_single_complex& v0, const simd_single_complex& v1,
                   const simd_single_complex& v2, const simd_single_complex& v3)
    : simd_compl(simd_half(v0, v1), simd_half(v2, v3))
{}

template<class Simd_tag>
force_inline
simd_compl<float, 256, Simd_tag>::simd_compl(float re_0, float im_0, float re_1, float im_1,
                   float re_2, float im_2, float re_3, float im_3)
    : data(re_0, im_0, re_1, im_1, re_2, im_2, re_3, im_3)
{};

template<class Simd_tag>
template<class Tag>
force_inline
simd_compl<float, 256, Simd_tag>::simd_compl(const simd_compl<float, 256, Tag>& s)
    : data(s.data)
{}

template<class Simd_tag>
force_inline
simd_compl<float, 256, Simd_tag> simd_compl<float, 256, Simd_tag>::zero()
{
    return impl_type::zero();
}

template<class Simd_tag>
force_inline simd_compl<float, 256, Simd_tag>
simd_compl<float, 256, Simd_tag>::broadcast(const simd_single_complex* arr)
{
    return simd_compl(arr[0]);
}

template<class Simd_tag>
force_inline simd_compl<float, 256, Simd_tag>
simd_compl<float, 256, Simd_tag>::broadcast(const simd_single_complex& arr)
{
    return simd_compl(arr);
};

template<class Simd_tag>
force_inline simd_compl<float, 256, Simd_tag>
simd_compl<float, 256, Simd_tag>::broadcast(const float* arr)
{
    return simd_compl(arr[0]);
}

template<class Simd_tag>
force_inline simd_compl<float, 256, Simd_tag>
simd_compl<float, 256, Simd_tag>::broadcast(const float& arr)
{
    return simd_compl(arr);
};

template<class Simd_tag>
force_inline simd_compl<float, 256, Simd_tag> 
simd_compl<float, 256, Simd_tag>::load(const simd_single_complex* arr, std::true_type aligned)
{
    return impl_type::load((const float*)arr, aligned);
};

template<class Simd_tag>
force_inline simd_compl<float, 256, Simd_tag> 
simd_compl<float, 256, Simd_tag>::load(const simd_single_complex* arr, std::false_type not_aligned)
{
    return impl_type::load((const float*)arr, not_aligned);
};

template<class Simd_tag>
force_inline void 
simd_compl<float, 256, Simd_tag>::store(simd_single_complex* arr, std::true_type aligned) const
{
    data.store((float*)arr, aligned);
};

template<class Simd_tag>
force_inline void 
simd_compl<float, 256, Simd_tag>::store(simd_single_complex* arr, std::false_type not_aligned) const
{
    data.store((float*)arr, not_aligned);
};

template<class Simd_tag>
force_inline
simd_single_complex simd_compl<float, 256, Simd_tag>::get(int pos) const
{
    const simd_single_complex* ptr  = this->get_raw_ptr();
    return simd_single_complex(ptr[pos]);
};

template<class Simd_tag>
force_inline
simd_single_complex simd_compl<float, 256, Simd_tag>::first() const
{
    return simd_single_complex(get_raw_ptr()[0]);
};

template<class Simd_tag>
force_inline
const simd_single_complex*
simd_compl<float, 256, Simd_tag>::get_raw_ptr() const
{
    return reinterpret_cast<const simd_single_complex*>(data.get_raw_ptr());
}

template<class Simd_tag>
force_inline
simd_single_complex*
simd_compl<float, 256, Simd_tag>::get_raw_ptr()
{
    return reinterpret_cast<simd_single_complex*>(data.get_raw_ptr());
}

template<class Simd_tag>
force_inline
void simd_compl<float, 256, Simd_tag>::set(int pos, const simd_single_complex& val)
{
    simd_single_complex* ptr    = this->get_raw_ptr();
    ptr[pos]                    = val;
};

template<class Simd_tag>
template<int Step>
force_inline
void simd_compl<float, 256, Simd_tag>::scatter(simd_single_complex* arr0) const
{
    float* arr          = (float*)arr0;
    const float* ptr    = data.get_raw_ptr();

    //no scatter intrinsic
    arr[0*Step*2]      = ptr[0];
    arr[0*Step*2+1]    = ptr[1];
    arr[1*Step*2]      = ptr[2];
    arr[1*Step*2+1]    = ptr[3];
    arr[2*Step*2]      = ptr[4];
    arr[2*Step*2+1]    = ptr[5];
    arr[3*Step*2]      = ptr[6];
    arr[3*Step*2+1]    = ptr[7];
};

template<class Simd_tag>
force_inline typename simd_compl<float, 256, Simd_tag>::simd_half
simd_compl<float, 256, Simd_tag>::extract_low() const
{
    return data.extract_low();
}

template<class Simd_tag>
force_inline typename simd_compl<float, 256, Simd_tag>::simd_half 
simd_compl<float, 256, Simd_tag>::extract_high() const
{
    return data.extract_high();
}

template<class Simd_tag>
force_inline simd_compl<double, 256, Simd_tag>
simd_compl<float, 256, Simd_tag>::convert_low_to_double() const
{
    return data.convert_low_to_double();
}

template<class Simd_tag>
force_inline simd_compl<double, 256, Simd_tag>
simd_compl<float, 256, Simd_tag>::convert_high_to_double() const
{
    return data.convert_high_to_double();
}

template<class Simd_tag>
force_inline simd_compl<float, 256, Simd_tag>& 
simd_compl<float, 256, Simd_tag>::operator+=(const simd_compl& x)
{
    *this = *this + x;
    return *this;
}

template<class Simd_tag>
force_inline simd_compl<float, 256, Simd_tag>& 
simd_compl<float, 256, Simd_tag>::operator-=(const simd_compl& x)
{
    *this = *this - x;
    return *this;
}

template<class Simd_tag>
force_inline simd_compl<float, 256, Simd_tag>& 
simd_compl<float, 256, Simd_tag>::operator*=(const simd_compl& x)
{
    *this = *this * x;
    return *this;
}

template<class Simd_tag>
force_inline simd_compl<float, 256, Simd_tag>& 
simd_compl<float, 256, Simd_tag>::operator/=(const simd_compl& x)
{
    *this = *this / x;
    return *this;
}

}}
