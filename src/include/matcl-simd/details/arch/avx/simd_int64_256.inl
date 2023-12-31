/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/arch/avx/simd_int64_256.h"

namespace matcl { namespace simd
{

//-------------------------------------------------------------------
//                          AVX INT64_T
//-------------------------------------------------------------------

force_inline
simd<int64_t, 256, avx_tag>::simd(int32_t val)
    : data(_mm256_set1_epi64x(val)) 
{}

force_inline
simd<int64_t, 256, avx_tag>::simd(int64_t val)
    : data(_mm256_set1_epi64x(val)) 
{}

force_inline
simd<int64_t, 256, avx_tag>::simd(int64_t v1, int64_t v2, int64_t v3, int64_t v4) 
    : data(_mm256_setr_epi64x(v1, v2, v3, v4)) 
{}

force_inline
simd<int64_t, 256, avx_tag>::simd(const simd_half& lo, const simd_half& hi)
    : data(_mm256_setr_m128i(lo.data, hi.data))
{}

force_inline
simd<int64_t, 256, avx_tag>::simd(const simd_half& lo_hi)
    : data(_mm256_setr_m128i(lo_hi.data, lo_hi.data))
{}

force_inline
simd<int64_t, 256, avx_tag>::simd(const impl_type& v)
    : data(v)
{};

force_inline
simd<int64_t, 256, avx_tag>::simd(const simd<int64_t, 256, nosimd_tag>& s)
    : data(_mm256_load_si256((const __m256i*)(s.data)))
{}

force_inline
simd<int64_t, 256, avx_tag>::simd(const simd<int64_t, 256, sse_tag>& s)
    : simd(s.data[0], s.data[1])
{}

force_inline
simd<int64_t, 256, avx_tag>::simd(const simd<int64_t, 128, scalar_sse_tag>& s)
{
    #if MATCL_ARCHITECTURE_HAS_AVX2
        data = _mm256_broadcastq_epi64(s.data);
    #else
        data = _mm256_set1_epi64x(s.first());
    #endif
}

force_inline
simd<int64_t, 256, avx_tag>::simd(const simd<int64_t, 128, scalar_nosimd_tag>& s)
    :simd(s.first())
{}


force_inline
int64_t simd<int64_t, 256, avx_tag>::get(int pos) const
{ 
    return get_raw_ptr()[pos] ; 
};

force_inline
int64_t simd<int64_t, 256, avx_tag>::first() const
{ 
    __m128i ds  = _mm256_castsi256_si128(data);
    return missing::mm_cvtsi128_si64(ds);
};

force_inline
void simd<int64_t, 256, avx_tag>::set(int pos, int64_t val)
{ 
    get_raw_ptr()[pos] = val; 
};

force_inline
const int64_t* simd<int64_t, 256, avx_tag>::get_raw_ptr() const
{ 
    return reinterpret_cast<const int64_t*>(&data); 
};

force_inline
int64_t* simd<int64_t, 256, avx_tag>::get_raw_ptr()
{ 
    return reinterpret_cast<int64_t*>(&data); 
};

force_inline simd<int64_t, 256, avx_tag>::simd_half
simd<int64_t, 256, avx_tag>::extract_low() const
{
    return _mm256_castsi256_si128(data);
}

force_inline simd<int64_t, 256, avx_tag>::simd_half
simd<int64_t, 256, avx_tag>::extract_high() const
{
    return _mm256_extractf128_si256(data, 1);
}

template<int I1, int I2, int I3, int I4>
force_inline simd<int64_t, 256, avx_tag>
simd<int64_t, 256, avx_tag>::select() const
{
    return this->reinterpret_as_double().select<I1, I2, I3, I4>().reinterpret_as_int64();
};

force_inline
simd<int64_t, 256, avx_tag> simd<int64_t, 256, avx_tag>::zero()
{
    impl_type data  = _mm256_setzero_si256();
    return data;
}

force_inline
simd<int64_t, 256, avx_tag> simd<int64_t, 256, avx_tag>::one()
{
    return simd(1);
}

force_inline
simd<int64_t, 256, avx_tag> simd<int64_t, 256, avx_tag>::minus_one()
{
    return simd(-1);
}

force_inline simd<int64_t, 256, avx_tag> 
simd<int64_t, 256, avx_tag>::load(const int64_t* arr, std::true_type aligned)
{
    (void)aligned;
    return _mm256_load_si256((const __m256i*)arr);
};

force_inline simd<int64_t, 256, avx_tag> 
simd<int64_t, 256, avx_tag>::load(const int64_t* arr, std::false_type not_aligned)
{
    (void)not_aligned;
    return _mm256_loadu_si256((const __m256i*)arr);
};

force_inline simd<int64_t, 256, avx_tag> 
simd<int64_t, 256, avx_tag>::gather(const int64_t* arr, const simd_int32_half& ind)
{
    #if MATCL_ARCHITECTURE_HAS_AVX2
        return _mm256_i32gather_epi64(arr, ind.data, 8);
    #else
        simd<int64_t, 256, avx_tag> res;
        int64_t* res_ptr        = res.get_raw_ptr();
        const int32_t* ind_ptr  = ind.get_raw_ptr();

        for (int i = 0; i < vector_size; ++i)
            res_ptr[i]  = arr[ind_ptr[i]];

        return res;
    #endif
}

force_inline simd<int64_t, 256, avx_tag> 
simd<int64_t, 256, avx_tag>::gather(const int64_t* arr, const simd_int32& ind)
{
    return gather(arr, ind.extract_low());
}

force_inline simd<int64_t, 256, avx_tag> 
simd<int64_t, 256, avx_tag>::gather(const int64_t* arr, const simd_int64& ind)
{
    #if MATCL_ARCHITECTURE_HAS_AVX2
        return _mm256_i64gather_epi64(arr, ind.data, 8);
    #else
        simd<int64_t, 256, avx_tag> res;
        int64_t* res_ptr        = res.get_raw_ptr();
        const int64_t* ind_ptr  = ind.get_raw_ptr();

        for (int i = 0; i < vector_size; ++i)
            res_ptr[i]  = arr[ind_ptr[i]];

        return res;
    #endif
}

force_inline simd<int64_t, 256, avx_tag> 
simd<int64_t, 256, avx_tag>::broadcast(const int64_t* arr)
{
    __m256d tmp = _mm256_broadcast_sd((const double*)arr);
    return _mm256_castpd_si256(tmp);
};

force_inline simd<int64_t, 256, avx_tag> 
simd<int64_t, 256, avx_tag>::broadcast(const int64_t& arr)
{
    __m256d tmp = _mm256_broadcast_sd((const double*)&arr);
    return _mm256_castpd_si256(tmp);
};

force_inline void 
simd<int64_t, 256, avx_tag>::store(int64_t* arr, std::true_type aligned) const
{
    (void)aligned;
    _mm256_store_si256((__m256i*)arr, data);
};

force_inline void 
simd<int64_t, 256, avx_tag>::store(int64_t* arr, std::false_type not_aligned) const
{
    (void)not_aligned;
    _mm256_storeu_si256((__m256i*)arr, data);
};

force_inline simd<int32_t, 128, sse_tag> 
simd<int64_t, 256, avx_tag>::convert_to_int32() const
{
    // SIMD intrinsic not available
    simd<int32_t, 128, sse_tag>  res;

    int32_t* res_ptr    = res.get_raw_ptr();
    const int64_t* ptr  = this->get_raw_ptr();

    for (int i = 0; i < vector_size; ++i)
        res_ptr[i]  = scalar_func::convert_int64_int32(ptr[i]);

    return res;
};

force_inline simd<float, 128, sse_tag> 
simd<int64_t, 256, avx_tag>::convert_to_float() const
{
    // SIMD intrinsic not available
    simd<float, 128, sse_tag>  res;

    float* res_ptr      = res.get_raw_ptr();
    const int64_t* ptr  = this->get_raw_ptr();

    for (int i = 0; i < vector_size; ++i)
        res_ptr[i]  = scalar_func::convert_int64_float(ptr[i]);

    return res;
};

force_inline simd<double, 256, avx_tag> 
simd<int64_t, 256, avx_tag>::convert_to_double() const
{
    simd<double, 256, avx_tag> ret;

    double* ret_ptr     = ret.get_raw_ptr();
    const int64_t* ptr  = this->get_raw_ptr();

    for (int i = 0; i < vector_size; ++i)
        ret_ptr[i]      = scalar_func::convert_int64_double(ptr[i]);
    
    return ret;
};

force_inline simd<double, 256, avx_tag> 
simd<int64_t, 256, avx_tag>::reinterpret_as_double() const
{
    return _mm256_castsi256_pd(data);
}

force_inline simd<float, 256, avx_tag> 
simd<int64_t, 256, avx_tag>::reinterpret_as_float() const
{
    return _mm256_castsi256_ps(data);
}

force_inline simd<int32_t, 256, avx_tag> 
simd<int64_t, 256, avx_tag>::reinterpret_as_int32() const
{
    return data;
};

template<int Step>
force_inline
void simd<int64_t, 256, avx_tag>::scatter(int64_t* arr) const
{
    const int64_t* ptr = get_raw_ptr();

    //no scatter intrinsic
    arr[0*Step] = ptr[0];
    arr[1*Step] = ptr[1];
    arr[2*Step] = ptr[2];
    arr[3*Step] = ptr[3];
};

force_inline simd<int64_t, 256, avx_tag>& 
simd<int64_t, 256, avx_tag>::operator+=(const simd& x)
{
    *this = *this + x;
    return *this;
}

force_inline simd<int64_t, 256, avx_tag>& 
simd<int64_t, 256, avx_tag>::operator-=(const simd& x)
{
    *this = *this - x;
    return *this;
}

force_inline simd<int64_t, 256, avx_tag>& 
simd<int64_t, 256, avx_tag>::operator*=(const simd& x)
{
    *this = *this * x;
    return *this;
}

}}
