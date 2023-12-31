/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/arch/nosimd/simd_int32_256.h"

#pragma warning(push)
#pragma warning(disable : 4127) // conditional expression is constant

namespace matcl { namespace simd
{

//-------------------------------------------------------------------
//                          GENERAL int32_t
//-------------------------------------------------------------------

force_inline
simd<int32_t, 256, nosimd_tag>::simd(int32_t val) 
{
    data[0] = val;
    data[1] = val;
    data[2] = val;
    data[3] = val;
    data[4] = val;
    data[5] = val;
    data[6] = val;
    data[7] = val;
}

force_inline
simd<int32_t, 256, nosimd_tag>::simd(const simd_half& lo_hi)
{
    data[0] = lo_hi.data[0];
    data[1] = lo_hi.data[1];
    data[2] = lo_hi.data[2];
    data[3] = lo_hi.data[3];
    data[4] = lo_hi.data[0];
    data[5] = lo_hi.data[1];
    data[6] = lo_hi.data[2];
    data[7] = lo_hi.data[3];
}

force_inline
simd<int32_t, 256, nosimd_tag>::simd(const simd_half& lo, const simd_half& hi)
{
    data[0] = lo.data[0];
    data[1] = lo.data[1];
    data[2] = lo.data[2];
    data[3] = lo.data[3];
    data[4] = hi.data[0];
    data[5] = hi.data[1];
    data[6] = hi.data[2];
    data[7] = hi.data[3];
}

force_inline
simd<int32_t, 256, nosimd_tag>::simd(int32_t v1, int32_t v2, int32_t v3, int32_t v4, int32_t v5, int32_t v6, int32_t v7, int32_t v8) 
{
    data[0] = v1;
    data[1] = v2;
    data[2] = v3;
    data[3] = v4;
    data[4] = v5;
    data[5] = v6;
    data[6] = v7;
    data[7] = v8;
}

#if MATCL_ARCHITECTURE_HAS_SSE2
    force_inline
    simd<int32_t, 256, nosimd_tag>::simd(const simd<int32_t, 256, sse_tag>& s)
    {
        s.store(data, std::true_type());
    }

    force_inline
    simd<int32_t, 256, nosimd_tag>::simd(const simd<int32_t, 128, scalar_sse_tag>& s)
        :simd(s.first())
    {}
#endif

#if MATCL_ARCHITECTURE_HAS_AVX
    force_inline
    simd<int32_t, 256, nosimd_tag>::simd(const simd<int32_t, 256, avx_tag>& s)
    {
        s.store(data, std::true_type());
    }
#endif

force_inline
simd<int32_t, 256, nosimd_tag>::simd(const simd<int32_t, 128, scalar_nosimd_tag>& s)
    :simd(s.first())
{}

force_inline
int32_t simd<int32_t, 256, nosimd_tag>::get(int pos) const  
{ 
    return data[pos] ; 
};

force_inline
int32_t simd<int32_t, 256, nosimd_tag>::first() const  
{ 
    return data[0]; 
};

force_inline
void simd<int32_t, 256, nosimd_tag>::set(int pos, int32_t val)
{ 
    data[pos] = val; 
};

force_inline
const int32_t* simd<int32_t, 256, nosimd_tag>::get_raw_ptr() const
{ 
    return data; 
};

force_inline
int32_t* simd<int32_t, 256, nosimd_tag>::get_raw_ptr()
{ 
    return data; 
};

force_inline simd<int32_t, 256, nosimd_tag>::simd_half
simd<int32_t, 256, nosimd_tag>::extract_low() const
{
    return simd_half(data[0], data[1], data[2], data[3]);
}

force_inline simd<int32_t, 256, nosimd_tag>::simd_half
simd<int32_t, 256, nosimd_tag>::extract_high() const
{
    return simd_half(data[4], data[5], data[6], data[7]);
}

template<int I1, int I2, int I3, int I4, int I5, int I6, int I7, int I8>
force_inline simd<int32_t, 256, nosimd_tag>
simd<int32_t, 256, nosimd_tag>::select() const
{
    static_assert(I1 >= 0 && I1 <= 7, "invalid index in select function");
    static_assert(I2 >= 0 && I2 <= 7, "invalid index in select function");
    static_assert(I3 >= 0 && I3 <= 7, "invalid index in select function");
    static_assert(I4 >= 0 && I4 <= 7, "invalid index in select function");
    static_assert(I5 >= 0 && I5 <= 7, "invalid index in select function");
    static_assert(I6 >= 0 && I6 <= 7, "invalid index in select function");
    static_assert(I7 >= 0 && I7 <= 7, "invalid index in select function");
    static_assert(I8 >= 0 && I8 <= 7, "invalid index in select function");

    if (I1 == 0 && I2 == 1 && I3 == 2 && I4 == 3 && I5 == 4 && I6 == 5 && I7 == 6 && I8 == 7) 
        return *this;

    simd<int32_t, 256, nosimd_tag> ret;
    ret.data[0] = data[I1];
    ret.data[1] = data[I2];
    ret.data[2] = data[I3];
    ret.data[3] = data[I4];
    ret.data[4] = data[I5];
    ret.data[5] = data[I6];
    ret.data[6] = data[I7];
    ret.data[7] = data[I8];

    return ret;
};

force_inline
simd<int32_t, 256, nosimd_tag> simd<int32_t, 256, nosimd_tag>::zero()
{
    simd<int32_t, 256, nosimd_tag> ret;

    ret.data[0] = 0;
    ret.data[1] = 0;
    ret.data[2] = 0;
    ret.data[3] = 0;
    ret.data[4] = 0;
    ret.data[5] = 0;
    ret.data[6] = 0;
    ret.data[7] = 0;

    return ret;
}

force_inline
simd<int32_t, 256, nosimd_tag> simd<int32_t, 256, nosimd_tag>::one()
{
    simd<int32_t, 256, nosimd_tag> ret;

    ret.data[0] = 1;
    ret.data[1] = 1;
    ret.data[2] = 1;
    ret.data[3] = 1;
    ret.data[4] = 1;
    ret.data[5] = 1;
    ret.data[6] = 1;
    ret.data[7] = 1;

    return ret;
}

force_inline
simd<int32_t, 256, nosimd_tag> simd<int32_t, 256, nosimd_tag>::minus_one()
{
    simd<int32_t, 256, nosimd_tag> ret;

    ret.data[0] = -1;
    ret.data[1] = -1;
    ret.data[2] = -1;
    ret.data[3] = -1;
    ret.data[4] = -1;
    ret.data[5] = -1;
    ret.data[6] = -1;
    ret.data[7] = -1;

    return ret;
}

force_inline simd<int32_t, 256, nosimd_tag> 
simd<int32_t, 256, nosimd_tag>::load(const int32_t* arr, std::true_type aligned)
{
    (void)aligned;
    simd<int32_t, 256, nosimd_tag> ret;

    ret.data[0] = arr[0];
    ret.data[1] = arr[1];
    ret.data[2] = arr[2];
    ret.data[3] = arr[3];
    ret.data[4] = arr[4];
    ret.data[5] = arr[5];
    ret.data[6] = arr[6];
    ret.data[7] = arr[7];

    return ret;
};

force_inline simd<int32_t, 256, nosimd_tag> 
simd<int32_t, 256, nosimd_tag>::load(const int32_t* arr, std::false_type not_aligned)
{
    (void)not_aligned;
    simd<int32_t, 256, nosimd_tag> ret;

    ret.data[0] = arr[0];
    ret.data[1] = arr[1];
    ret.data[2] = arr[2];
    ret.data[3] = arr[3];
    ret.data[4] = arr[4];
    ret.data[5] = arr[5];
    ret.data[6] = arr[6];
    ret.data[7] = arr[7];

    return ret;
};

force_inline simd<int32_t, 256, nosimd_tag> 
simd<int32_t, 256, nosimd_tag>::gather(const int32_t* arr, const simd_int32& ind)
{
    simd<int32_t, 256, nosimd_tag> ret;

    ret.data[0] = arr[ind.data[0]];
    ret.data[1] = arr[ind.data[1]];
    ret.data[2] = arr[ind.data[2]];
    ret.data[3] = arr[ind.data[3]];
    ret.data[4] = arr[ind.data[4]];
    ret.data[5] = arr[ind.data[5]];
    ret.data[6] = arr[ind.data[6]];
    ret.data[7] = arr[ind.data[7]];

    return ret;
}

force_inline simd<int32_t, 256, nosimd_tag> 
simd<int32_t, 256, nosimd_tag>::gather(const int32_t* arr, const simd_int64& ind)
{
    simd<int32_t, 256, nosimd_tag> ret;

    ret.data[0] = arr[ind.data[0]];
    ret.data[1] = arr[ind.data[1]];
    ret.data[2] = arr[ind.data[2]];
    ret.data[3] = arr[ind.data[3]];

    ret.data[4] = 0;
    ret.data[5] = 0;
    ret.data[6] = 0;
    ret.data[7] = 0;

    return ret;
}

force_inline simd<int32_t, 256, nosimd_tag> 
simd<int32_t, 256, nosimd_tag>::broadcast(const int32_t* arr)
{
    simd<int32_t, 256, nosimd_tag> ret;

    ret.data[0] = arr[0];
    ret.data[1] = arr[0];
    ret.data[2] = arr[0];
    ret.data[3] = arr[0];
    ret.data[4] = arr[0];
    ret.data[5] = arr[0];
    ret.data[6] = arr[0];
    ret.data[7] = arr[0];

    return ret;
};

force_inline simd<int32_t, 256, nosimd_tag> 
simd<int32_t, 256, nosimd_tag>::broadcast(const int32_t& arr)
{
    simd<int32_t, 256, nosimd_tag> ret;

    ret.data[0] = arr;
    ret.data[1] = arr;
    ret.data[2] = arr;
    ret.data[3] = arr;
    ret.data[4] = arr;
    ret.data[5] = arr;
    ret.data[6] = arr;
    ret.data[7] = arr;

    return ret;
};

force_inline void 
simd<int32_t, 256, nosimd_tag>::store(int32_t* arr, std::true_type aligned) const
{
    (void)aligned;
    arr[0] = data[0];
    arr[1] = data[1];
    arr[2] = data[2];
    arr[3] = data[3];
    arr[4] = data[4];
    arr[5] = data[5];
    arr[6] = data[6];
    arr[7] = data[7];
};

force_inline void 
simd<int32_t, 256, nosimd_tag>::store(int32_t* arr, std::false_type not_aligned) const
{
    (void)not_aligned;
    arr[0] = data[0];
    arr[1] = data[1];
    arr[2] = data[2];
    arr[3] = data[3];
    arr[4] = data[4];
    arr[5] = data[5];
    arr[6] = data[6];
    arr[7] = data[7];
};

force_inline simd<int64_t, 256, nosimd_tag>
simd<int32_t, 256, nosimd_tag>::convert_low_to_int64() const
{
    simd<int64_t, 256, nosimd_tag> res;
    res.data[0] = scalar_func::convert_int32_int64(data[0]);
    res.data[1] = scalar_func::convert_int32_int64(data[1]);
    res.data[2] = scalar_func::convert_int32_int64(data[2]);
    res.data[3] = scalar_func::convert_int32_int64(data[3]);

    return res;
};

force_inline simd<int64_t, 256, nosimd_tag>
simd<int32_t, 256, nosimd_tag>::convert_high_to_int64() const
{
    simd<int64_t, 256, nosimd_tag> res;
    res.data[0] = scalar_func::convert_int32_int64(data[4]);
    res.data[1] = scalar_func::convert_int32_int64(data[5]);
    res.data[2] = scalar_func::convert_int32_int64(data[6]);
    res.data[3] = scalar_func::convert_int32_int64(data[7]);

    return res;
}

force_inline simd<double, 256, nosimd_tag>
simd<int32_t, 256, nosimd_tag>::convert_low_to_double() const
{
    simd<double, 256, nosimd_tag> res;
    res.data[0] = scalar_func::convert_int32_double(data[0]);
    res.data[1] = scalar_func::convert_int32_double(data[1]);
    res.data[2] = scalar_func::convert_int32_double(data[2]);
    res.data[3] = scalar_func::convert_int32_double(data[3]);

    return res;
};

force_inline simd<double, 256, nosimd_tag>
simd<int32_t, 256, nosimd_tag>::convert_high_to_double() const
{
    simd<double, 256, nosimd_tag> res;
    res.data[0] = scalar_func::convert_int32_double(data[4]);
    res.data[1] = scalar_func::convert_int32_double(data[5]);
    res.data[2] = scalar_func::convert_int32_double(data[6]);
    res.data[3] = scalar_func::convert_int32_double(data[7]);

    return res;
}

force_inline simd<float, 256, nosimd_tag>
simd<int32_t, 256, nosimd_tag>::convert_to_float() const
{
    simd<float, 256, nosimd_tag> res;
    res.data[0] = scalar_func::convert_int32_float(data[0]);
    res.data[1] = scalar_func::convert_int32_float(data[1]);
    res.data[2] = scalar_func::convert_int32_float(data[2]);
    res.data[3] = scalar_func::convert_int32_float(data[3]);
    res.data[4] = scalar_func::convert_int32_float(data[4]);
    res.data[5] = scalar_func::convert_int32_float(data[5]);
    res.data[6] = scalar_func::convert_int32_float(data[6]);
    res.data[7] = scalar_func::convert_int32_float(data[7]);

    return res;
}

force_inline simd<int64_t, 256, nosimd_tag>
simd<int32_t, 256, nosimd_tag>::reinterpret_as_int64() const
{
    return *reinterpret_cast<const simd_int64*>(this);
}

force_inline simd<double, 256, nosimd_tag>
simd<int32_t, 256, nosimd_tag>::reinterpret_as_double() const
{
    return *reinterpret_cast<const simd_double*>(this);
}

force_inline simd<float, 256, nosimd_tag>
simd<int32_t, 256, nosimd_tag>::reinterpret_as_float() const
{
    return *reinterpret_cast<const simd_float*>(this);
}

template<int Step>
force_inline
void simd<int32_t, 256, nosimd_tag>::scatter(int32_t* arr) const
{
    arr[0*Step] = data[0];
    arr[1*Step] = data[1];
    arr[2*Step] = data[2];
    arr[3*Step] = data[3];
    arr[4*Step] = data[4];
    arr[5*Step] = data[5];
    arr[6*Step] = data[6];
    arr[7*Step] = data[7];
};

force_inline simd<int32_t, 256, nosimd_tag>& 
simd<int32_t, 256, nosimd_tag>::operator+=(const simd& x)
{
    *this = *this + x;
    return *this;
}

force_inline simd<int32_t, 256, nosimd_tag>& 
simd<int32_t, 256, nosimd_tag>::operator-=(const simd& x)
{
    *this = *this - x;
    return *this;
}

force_inline simd<int32_t, 256, nosimd_tag>& 
simd<int32_t, 256, nosimd_tag>::operator*=(const simd& x)
{
    *this = *this * x;
    return *this;
}

}}

#pragma warning(pop)