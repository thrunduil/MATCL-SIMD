/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */
#pragma once

#include "matcl-simd/arch/sse/simd_int64_128.h"
#include "matcl-simd/details/arch/sse/func/missing_intrinsics.h"

namespace matcl { namespace simd
{

//-------------------------------------------------------------------
//                          SSE2 SCALAR INT64_T
//-------------------------------------------------------------------

force_inline
simd<int64_t, 128, scalar_sse_tag>::simd(int32_t val)
    : data(_mm_set1_epi64x(val)) 
{}

force_inline
simd<int64_t, 128, scalar_sse_tag>::simd(int64_t val)
    : data(_mm_set1_epi64x(val)) 
{}

force_inline
simd<int64_t, 128, scalar_sse_tag>::simd(const impl_type& v)
    : data(v) 
{};

force_inline
simd<int64_t, 128, scalar_sse_tag>::simd(const simd<int64_t, 128, nosimd_tag>& s)
    : data(_mm_load_si128((const __m128i*)s.data))
{};

force_inline
simd<int64_t, 128, scalar_sse_tag>::simd(const simd<int64_t, 128, sse_tag>& s)
    : data(s.data)
{};

force_inline
simd<int64_t, 128, scalar_sse_tag>::simd(const simd<int64_t, 128, scalar_nosimd_tag>& s)
    : simd(broadcast(s.data))
{};

force_inline simd<int64_t, 128, scalar_sse_tag> 
simd<int64_t, 128, scalar_sse_tag>::broadcast(const int64_t* arr)
{ 
    return _mm_set1_epi64x(arr[0]);
};

force_inline simd<int64_t, 128, scalar_sse_tag>
simd<int64_t, 128, scalar_sse_tag>::broadcast(const int64_t& arr)
{ 
    return _mm_set1_epi64x(arr);
};

force_inline simd<int64_t, 128, scalar_sse_tag> 
simd<int64_t, 128, scalar_sse_tag>::set_lower(int64_t v)
{
    return missing::mm_cvtsi64_si128(v);
};

force_inline simd<int32_t, 128, scalar_sse_tag>
simd<int64_t, 128, scalar_sse_tag>::convert_to_int32() const
{
    int32_t val = scalar_func::convert_int64_int32(first());
    return simd<int32_t, 128, scalar_sse_tag>(val);
};

force_inline simd<double, 128, scalar_sse_tag> 
simd<int64_t, 128, scalar_sse_tag>::convert_to_double() const
{
    double val = scalar_func::convert_int64_double(first());
    return simd<double, 128, scalar_sse_tag>(val);
};

force_inline simd<float, 128, scalar_sse_tag> 
simd<int64_t, 128, scalar_sse_tag>::convert_to_float() const
{
    float val = scalar_func::convert_int64_float(first());
    return simd<float, 128, scalar_sse_tag>(val);
};

force_inline simd<double, 128, scalar_sse_tag>
simd<int64_t, 128, scalar_sse_tag>::reinterpret_as_double() const
{
    return _mm_castsi128_pd(data);
}

force_inline simd<float, 128, scalar_sse_tag>
simd<int64_t, 128, scalar_sse_tag>::reinterpret_as_float() const
{
    return _mm_castsi128_ps(data);
}

force_inline simd<int32_t, 128, scalar_sse_tag>
simd<int64_t, 128, scalar_sse_tag>::reinterpret_as_int32() const
{
    return data;
}

force_inline simd<int32_t, 128, sse_tag>
simd<int32_t, 128, scalar_sse_tag>::as_vector() const
{
    return data;
}

force_inline
int64_t simd<int64_t, 128, scalar_sse_tag>::get(int pos) const
{ 
    (void)pos;
    return first();
};

force_inline
int64_t simd<int64_t, 128, scalar_sse_tag>::first() const
{ 
    return missing::mm_cvtsi128_si64(data); 
};

force_inline
void simd<int64_t, 128, scalar_sse_tag>::set(int pos, int64_t val)
{ 
    (void)pos;
    data = _mm_set1_epi64x(val);
};

force_inline
const int64_t* simd<int64_t, 128, scalar_sse_tag>::get_raw_ptr() const
{ 
    return reinterpret_cast<const int64_t*>(&data); 
};

force_inline
int64_t* simd<int64_t, 128, scalar_sse_tag>::get_raw_ptr()
{ 
    return reinterpret_cast<int64_t*>(&data); 
};

force_inline
simd<int64_t, 128, scalar_sse_tag> simd<int64_t, 128, scalar_sse_tag>::zero()
{
    impl_type data  = _mm_setzero_si128();
    return data;
}

force_inline
simd<int64_t, 128, scalar_sse_tag> simd<int64_t, 128, scalar_sse_tag>::one()
{
    return simd(1);
}

force_inline
simd<int64_t, 128, scalar_sse_tag> simd<int64_t, 128, scalar_sse_tag>::minus_one()
{
    return simd(-1);
}

force_inline simd<int64_t, 128, scalar_sse_tag> 
simd<int64_t, 128, scalar_sse_tag>::load(const int64_t* arr, std::true_type aligned)
{
    (void)aligned;
    return _mm_set1_epi64x(arr[0]);
};

force_inline simd<int64_t, 128, scalar_sse_tag> 
simd<int64_t, 128, scalar_sse_tag>::load(const int64_t* arr, std::false_type not_aligned)
{
    (void)not_aligned;
    return _mm_set1_epi64x(arr[0]);
};

force_inline simd<int64_t, 128, scalar_sse_tag>
simd<int64_t, 128, scalar_sse_tag>::gather(const int64_t* arr, const simd_int32& ind)
{
    return simd(arr[ind.first()]);
}

force_inline simd<int64_t, 128, scalar_sse_tag>
simd<int64_t, 128, scalar_sse_tag>::gather(const int64_t* arr, const simd_int64& ind)
{
    return simd(arr[ind.first()]);
}

force_inline void 
simd<int64_t, 128, scalar_sse_tag>::store(int64_t* arr, std::true_type aligned) const
{
    (void)aligned;
    arr[0] = first();
};

force_inline void 
simd<int64_t, 128, scalar_sse_tag>::store(int64_t* arr, std::false_type not_aligned) const
{
    (void)not_aligned;
    arr[0] = first();
};

template<int Step>
force_inline
void simd<int64_t, 128, scalar_sse_tag>::scatter(int64_t* arr) const
{
    arr[0] = first();
};

force_inline simd<int64_t, 128, scalar_sse_tag>& 
simd<int64_t, 128, scalar_sse_tag>::operator+=(const simd& x)
{
    *this = *this + x;
    return *this;
}

force_inline simd<int64_t, 128, scalar_sse_tag>& 
simd<int64_t, 128, scalar_sse_tag>::operator-=(const simd& x)
{
    *this = *this - x;
    return *this;
}

force_inline simd<int64_t, 128, scalar_sse_tag>& 
simd<int64_t, 128, scalar_sse_tag>::operator*=(const simd& x)
{
    *this = *this * x;
    return *this;
}

}}
