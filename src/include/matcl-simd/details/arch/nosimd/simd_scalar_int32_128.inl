/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/arch/nosimd/simd_int32_128.h"

namespace matcl { namespace simd
{

//-------------------------------------------------------------------
//                          GENERIC int32_t
//-------------------------------------------------------------------

force_inline
simd<int32_t, 128, scalar_nosimd_tag>::simd(int32_t val)
{
    data = val;
}

#if MATCL_ARCHITECTURE_HAS_SSE2
    force_inline
    simd<int32_t, 128, scalar_nosimd_tag>::simd(const simd<int32_t, 128, sse_tag>& s)
        :data(s.first())
    {}

    force_inline
    simd<int32_t, 128, scalar_nosimd_tag>::simd(const simd<int32_t, 128, scalar_sse_tag>& s)
        :data(s.first())
    {};
#endif

force_inline
simd<int32_t, 128, scalar_nosimd_tag>::simd(const simd<int32_t, 128, nosimd_tag>& s)
    :data(s.first())
{}

force_inline simd<int32_t, 128, scalar_nosimd_tag> 
simd<int32_t, 128, scalar_nosimd_tag>::broadcast(const int32_t* arr)
{
    return simd(arr[0]);
};

force_inline simd<int32_t, 128, scalar_nosimd_tag> 
simd<int32_t, 128, scalar_nosimd_tag>::broadcast(const int32_t& arr)
{ 
    return simd(arr);
};

force_inline
int32_t simd<int32_t, 128, scalar_nosimd_tag>::get(int pos) const
{ 
    (void)pos;
    return data;
};

force_inline
int32_t simd<int32_t, 128, scalar_nosimd_tag>::first() const
{ 
    return data; 
};

force_inline
void simd<int32_t, 128, scalar_nosimd_tag>::set(int pos, int32_t val)
{ 
    (void)pos;
    data = val; 
};

force_inline
const int32_t* simd<int32_t, 128, scalar_nosimd_tag>::get_raw_ptr() const
{ 
    return &data; 
};

force_inline
int32_t* simd<int32_t, 128, scalar_nosimd_tag>::get_raw_ptr()
{ 
    return &data; 
};

force_inline
simd<int32_t, 128, scalar_nosimd_tag> simd<int32_t, 128, scalar_nosimd_tag>::zero()
{
    return simd(0);
}

force_inline
simd<int32_t, 128, scalar_nosimd_tag> simd<int32_t, 128, scalar_nosimd_tag>::one()
{
    return simd(1);
}

force_inline
simd<int32_t, 128, scalar_nosimd_tag> simd<int32_t, 128, scalar_nosimd_tag>::minus_one()
{
    return simd(-1);
}

force_inline simd<int32_t, 128, scalar_nosimd_tag> 
simd<int32_t, 128, scalar_nosimd_tag>::load(const int32_t* arr, std::true_type aligned)
{
    (void)aligned;
    return simd(arr[0]);
};

force_inline simd<int32_t, 128, scalar_nosimd_tag> 
simd<int32_t, 128, scalar_nosimd_tag>::load(const int32_t* arr, std::false_type not_aligned)
{
    (void)not_aligned;
    return simd(arr[0]);
};

force_inline simd<int32_t, 128, scalar_nosimd_tag>
simd<int32_t, 128, scalar_nosimd_tag>::gather(const int32_t* arr, const simd_int32& ind)
{
    return simd(arr[ind.first()]);
}

force_inline simd<int32_t, 128, scalar_nosimd_tag> 
simd<int32_t, 128, scalar_nosimd_tag>::gather(const int32_t* arr, const simd_int64& ind)
{
    return simd(arr[ind.first()]);
}

force_inline simd<int32_t, 128, scalar_nosimd_tag> 
simd<int32_t, 128, scalar_nosimd_tag>::set_lower(int32_t v)
{
    return simd(v);
};

force_inline
simd<int64_t, 128, scalar_nosimd_tag>
simd<int32_t, 128, scalar_nosimd_tag>::convert_to_int64() const
{
    return simd<int64_t, 128, scalar_nosimd_tag>(scalar_func::convert_int32_int64(data));
};

force_inline
simd<double, 128, scalar_nosimd_tag>
simd<int32_t, 128, scalar_nosimd_tag>::convert_to_double() const
{
    return simd<double, 128, scalar_nosimd_tag>(scalar_func::convert_int32_double(data));
};

force_inline
simd<float, 128, scalar_nosimd_tag>
simd<int32_t, 128, scalar_nosimd_tag>::convert_to_float() const
{
    return simd<float, 128, scalar_nosimd_tag>(scalar_func::convert_int32_float(data));
};

force_inline simd<float, 128, scalar_nosimd_tag>
simd<int32_t, 128, scalar_nosimd_tag>::reinterpret_as_float() const
{
    return *reinterpret_cast<const simd_float*>(this);
}

force_inline simd<int64_t, 128, scalar_nosimd_tag>
simd<int32_t, 128, scalar_nosimd_tag>::reinterpret_as_int64() const
{
    return *reinterpret_cast<const simd_int64*>(this);
}

force_inline simd<double, 128, scalar_nosimd_tag>
simd<int32_t, 128, scalar_nosimd_tag>::reinterpret_as_double() const
{
    return *reinterpret_cast<const simd_double*>(this);
}

force_inline simd<int32_t, 128, nosimd_tag>
simd<int32_t, 128, scalar_nosimd_tag>::as_vector() const
{
    return simd<int32_t, 128, nosimd_tag>(data);
}

force_inline void 
simd<int32_t, 128, scalar_nosimd_tag>::store(int32_t* arr, std::true_type aligned) const
{
    (void)aligned;
    arr[0] = data;
};

force_inline void 
simd<int32_t, 128, scalar_nosimd_tag>::store(int32_t* arr, std::false_type not_aligned) const
{
    (void)not_aligned;
    arr[0] = data;
};

template<int Step>
force_inline
void simd<int32_t, 128, scalar_nosimd_tag>::scatter(int32_t* arr) const
{
    arr[0*Step] = data;
};

force_inline simd<int32_t, 128, scalar_nosimd_tag>& 
simd<int32_t, 128, scalar_nosimd_tag>::operator+=(const simd& x)
{
    *this = *this + x;
    return *this;
}

force_inline simd<int32_t, 128, scalar_nosimd_tag>& 
simd<int32_t, 128, scalar_nosimd_tag>::operator-=(const simd& x)
{
    *this = *this - x;
    return *this;
}

force_inline simd<int32_t, 128, scalar_nosimd_tag>& 
simd<int32_t, 128, scalar_nosimd_tag>::operator*=(const simd& x)
{
    *this = *this * x;
    return *this;
}

}}
