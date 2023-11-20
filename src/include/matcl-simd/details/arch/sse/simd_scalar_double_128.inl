/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/arch/sse/simd_scalar_double_128.h"
#include "matcl-simd/details/arch/sse/func/missing_intrinsics.h"

namespace matcl { namespace simd
{

//-------------------------------------------------------------------
//                          SSE2 SCALAR DOUBLE
//-------------------------------------------------------------------

force_inline
simd<double, 128, scalar_sse_tag>::simd(int32_t val)
    : data(_mm_set1_pd(val)) 
{}

force_inline
simd<double, 128, scalar_sse_tag>::simd(int64_t val)
    : data(_mm_set1_pd(double(val))) 
{}

force_inline
simd<double, 128, scalar_sse_tag>::simd(float val)
    : data(_mm_set1_pd(val)) 
{}

force_inline
simd<double, 128, scalar_sse_tag>::simd(double val)
    : data(_mm_set1_pd(val)) 
{}

force_inline
simd<double, 128, scalar_sse_tag>::simd(const impl_type& v)
    : data(v) 
{};

force_inline
simd<double, 128, scalar_sse_tag>::simd(const simd<double, 128, nosimd_tag>& s)
    : data(_mm_load_pd(s.data))
{};

force_inline
simd<double, 128, scalar_sse_tag>::simd(const simd<double, 128, sse_tag>& s)
    : data(s.data)
{};

force_inline
simd<double, 128, scalar_sse_tag>::simd(const simd<double, 128, scalar_nosimd_tag>& s)
    : simd(broadcast(s.data))
{};

force_inline simd<double, 128, scalar_sse_tag> 
simd<double, 128, scalar_sse_tag>::broadcast(const double* arr)
{ 
    return _mm_load1_pd(arr);
};

force_inline simd<double, 128, scalar_sse_tag> 
simd<double, 128, scalar_sse_tag>::broadcast(const double& arr)
{ 
    return _mm_load1_pd(&arr);
};

force_inline simd<double, 128, scalar_sse_tag>
simd<double, 128, scalar_sse_tag>::set_lower(double v)
{
    return _mm_set_sd(v);
};

force_inline
simd<float, 128, scalar_sse_tag>
simd<double, 128, scalar_sse_tag>::convert_to_float() const
{
    return _mm_cvtpd_ps(data);
};

force_inline simd<int32_t, 128, scalar_sse_tag>
simd<double, 128, scalar_sse_tag>::convert_to_int32() const
{
    return _mm_cvtpd_epi32(data);
};

force_inline simd<int64_t, 128, scalar_sse_tag> 
simd<double, 128, scalar_sse_tag>::convert_to_int64() const
{
    int64_t val = scalar_func::convert_double_int64(first());
    return simd<int64_t, 128, scalar_sse_tag>(val);
};

force_inline simd<float, 128, scalar_sse_tag>
simd<double, 128, scalar_sse_tag>::reinterpret_as_float() const
{
    return _mm_castpd_ps(data);
}

force_inline simd<int32_t, 128, scalar_sse_tag>
simd<double, 128, scalar_sse_tag>::reinterpret_as_int32() const
{
    return _mm_castpd_si128(data);
}

force_inline simd<int64_t, 128, scalar_sse_tag>
simd<double, 128, scalar_sse_tag>::reinterpret_as_int64() const
{
    return _mm_castpd_si128(data);
}

force_inline simd<double, 128, sse_tag>
simd<double, 128, scalar_sse_tag>::as_vector() const
{
    return data;
}

force_inline
double simd<double, 128, scalar_sse_tag>::get(int pos) const
{ 
    (void)pos;
    return first();
};

force_inline
double simd<double, 128, scalar_sse_tag>::first() const
{ 
    return _mm_cvtsd_f64(data); 
};

force_inline
void simd<double, 128, scalar_sse_tag>::set(int pos, double val)
{
    (void)pos;
    data = _mm_set1_pd(val);
};

force_inline
const double* simd<double, 128, scalar_sse_tag>::get_raw_ptr() const
{ 
    return reinterpret_cast<const double*>(&data); 
};

force_inline
double* simd<double, 128, scalar_sse_tag>::get_raw_ptr()
{ 
    return reinterpret_cast<double*>(&data); 
};

force_inline
simd<double, 128, scalar_sse_tag> simd<double, 128, scalar_sse_tag>::zero()
{
    impl_type data  = _mm_setzero_pd();
    return data;
}

force_inline
simd<double, 128, scalar_sse_tag> simd<double, 128, scalar_sse_tag>::minus_zero()
{
    return simd(-0.0);
}

force_inline
simd<double, 128, scalar_sse_tag> simd<double, 128, scalar_sse_tag>::one()
{
    return simd(1.0);
}

force_inline
simd<double, 128, scalar_sse_tag> simd<double, 128, scalar_sse_tag>::minus_one()
{
    return simd(-1.0);
}

force_inline simd<double, 128, scalar_sse_tag> 
simd<double, 128, scalar_sse_tag>::load(const double* arr, std::true_type aligned)
{
    (void)aligned;
    return _mm_load1_pd(arr);
};

force_inline simd<double, 128, scalar_sse_tag> 
simd<double, 128, scalar_sse_tag>::load(const double* arr, std::false_type not_aligned)
{
    (void)not_aligned;
    return _mm_load1_pd(arr);
};

force_inline simd<double, 128, scalar_sse_tag> 
simd<double, 128, scalar_sse_tag>::gather(const double* arr, const simd_int32& ind)
{
    return simd(arr[ind.first()]);
}

force_inline simd<double, 128, scalar_sse_tag> 
simd<double, 128, scalar_sse_tag>::gather(const double* arr, const simd_int64& ind)
{
    return simd(arr[ind.first()]);
}

force_inline void 
simd<double, 128, scalar_sse_tag>::store(double* arr, std::true_type aligned) const
{
    (void)aligned;
    arr[0] = first();
};

force_inline void 
simd<double, 128, scalar_sse_tag>::store(double* arr, std::false_type not_aligned) const
{
    (void)not_aligned;
    arr[0] = first();
};

template<int Step>
force_inline
void simd<double, 128, scalar_sse_tag>::scatter(double* arr) const
{
    arr[0] = first();
};

force_inline simd<double, 128, scalar_sse_tag>& 
simd<double, 128, scalar_sse_tag>::operator+=(const simd& x)
{
    *this = *this + x;
    return *this;
}

force_inline simd<double, 128, scalar_sse_tag>& 
simd<double, 128, scalar_sse_tag>::operator-=(const simd& x)
{
    *this = *this - x;
    return *this;
}

force_inline simd<double, 128, scalar_sse_tag>& 
simd<double, 128, scalar_sse_tag>::operator*=(const simd& x)
{
    *this = *this * x;
    return *this;
}

force_inline simd<double, 128, scalar_sse_tag>& 
simd<double, 128, scalar_sse_tag>::operator/=(const simd& x)
{
    *this = *this / x;
    return *this;
}

}}
