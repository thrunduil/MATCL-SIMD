/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/details/arch/simd_impl.h"
#include "matcl-simd/details/complex/simd_complex_impl.h"
#include "matcl-simd/details/func/simd_func_complex_def.h"

namespace matcl { namespace simd { namespace details
{

template<class T, int Bits>
struct simd_compl_reverse<T, Bits, nosimd_tag>
{
    using simd_type = simd_compl<T, Bits, nosimd_tag>;
    
    static const int 
    vector_size     = simd_type::vector_size;

    force_inline
    static simd_type eval(const simd_type& x)
    {
        simd_type res;

        static const int last = 2*(vector_size - 1);

        for (int i = 0; i < 2*vector_size; i += 2)
        {
            res.data.data[i+0] = x.data.data[last - i + 0];
            res.data.data[i+1] = x.data.data[last - i + 1];
        }

        return res;
    }
};

template<class T, int Bits>
struct simd_compl_conj<T, Bits, nosimd_tag>
{
    using simd_type = simd_compl<T, Bits, nosimd_tag>;
    
    static const int 
    vector_size     = simd_type::vector_size;

    force_inline
    static simd_type eval(const simd_type& x)
    {
        simd_type res;

        static const int last = 2*(vector_size - 1);

        for (int i = 0; i < 2*vector_size; i += 2)
        {
            res.data.data[i+0] = x.data.data[i + 0];
            res.data.data[i+1] = -x.data.data[i + 1];
        }

        return res;
    }
};

template<>
struct simd_compl_reverse<double, 128, nosimd_tag>
{
    using simd_type = simd_compl<double, 128, nosimd_tag>;
    
    static const int 
    vector_size     = simd_type::vector_size;

    force_inline
    static simd_type eval(const simd_type& x)
    {
        return x;
    }
};

template<>
struct simd_compl_conj<double, 128, nosimd_tag>
{
    using simd_type = simd_compl<double, 128, nosimd_tag>;
    
    static const int 
    vector_size     = simd_type::vector_size;

    force_inline
    static simd_type eval(const simd_type& x)
    {
        return simd_type(x.data.data[0], -x.data.data[1]);
    }
};

template<class T, int Bits>
struct simd_compl_mult<T, Bits, nosimd_tag>
{
    using simd_type         = simd_compl<T, Bits, nosimd_tag>;
    using simd_real_type    = simd<T, Bits, nosimd_tag>;

    static const int 
    vector_size     = simd_type::vector_size;

    force_inline
    static simd_type eval(const simd_type& x, const simd_type& y)
    {
        simd_type res;

        for (int i = 0; i < vector_size; ++i)
            res.set(i, x.get(i) * y.get(i));

        return res;
    };

    force_inline
    static simd_type eval_rc(const simd_real_type& x, const simd_type& y)
    {
        simd_type res;

        for (int i = 0; i < 2*vector_size; i += 2)
        {
            res.data.data[i]    = x.data[i] * y.data.data[i];
            res.data.data[i+1]  = x.data[i+1] * y.data.data[i+1];
        };

        return res;
    }

    force_inline
    static simd_type eval_cr(const simd_type& x, const simd_real_type& y)
    {
        simd_type res;

        for (int i = 0; i < 2*vector_size; i += 2)
        {
            res.data.data[i]    = x.data.data[i] * y.data[i];
            res.data.data[i+1]  = x.data.data[i+1] * y.data[i+1];
        };

        return res;
    }
};

template<class T, int Bits>
struct simd_compl_div<T, Bits, nosimd_tag>
{
    using simd_type = simd_compl<T, Bits, nosimd_tag>;
    using simd_real = simd<T, Bits, nosimd_tag>;
    
    static const int 
    vector_size     = simd_type::vector_size;

    force_inline
    static simd_type eval(const simd_type& x, const simd_type& y)
    {
        simd_type res;

        for (int i = 0; i < vector_size; ++i)
            res.set(i, x.get(i) / y.get(i));

        return res;
    };

    force_inline
    static simd_type eval_rc(const simd_real& x, const simd_type& y)
    {
        simd_type res;

        for (int i = 0; i < vector_size; ++i)
            res.set(i, x.get(2*i) / y.get(i));

        return res;
    };

    force_inline
    static simd_type eval_cr(const simd_type& x, const simd_real& y)
    {
        simd_type res;

        for (int i = 0; i < 2*vector_size; i += 2)
        {
            res.data.data[i]    = x.data.data[i] / y.data[i];
            res.data.data[i+1]  = x.data.data[i+1] / y.data[i+1];
        }

        return res;
    }

};

template<class T, int Bits>
struct simd_compl_plus<T, Bits, nosimd_tag>
{
    using simd_type = simd_compl<T, Bits, nosimd_tag>;
    
    static const int 
    vector_size     = 2 * simd_type::vector_size;

    force_inline
    static simd_type eval(const simd_type& x, const simd_type& y)
    {
        simd_type res;

        for (int i = 0; i < vector_size; ++i)
            res.data.data[i] = x.data.data[i] + y.data.data[i];

        return res;
    };
};

template<class T, int Bits>
struct simd_compl_minus<T, Bits, nosimd_tag>
{
    using simd_type = simd_compl<T, Bits, nosimd_tag>;
    
    static const int 
    vector_size     = 2 * simd_type::vector_size;

    force_inline
    static simd_type eval(const simd_type& x, const simd_type& y)
    {
        simd_type res;

        for (int i = 0; i < vector_size; ++i)
            res.data.data[i] = x.data.data[i] - y.data.data[i];

        return res;
    };
};

template<class T, int Bits>
struct simd_compl_uminus<T, Bits, nosimd_tag>
{
    using simd_type = simd_compl<T, Bits, nosimd_tag>;
    
    static const int 
    vector_size     = 2 * simd_type::vector_size;

    force_inline
    static simd_type eval(const simd_type& x)
    {
        simd_type res;

        for (int i = 0; i < vector_size; ++i)
            res.data.data[i] = -x.data.data[i];

        return res;
    };
};

template<class T, int Bits>
struct simd_compl_horizontal_sum<T, Bits, nosimd_tag>
{
    using simd_type     = simd_compl<T, Bits, nosimd_tag>;
    using compl_type    = typename ms::details::complex_type<T>::type;
    
    static const int 
    vector_size     = 2 * simd_type::vector_size;

    force_inline
    static compl_type eval(const simd_type& x)
    {
        T res_re    = x.data.data[0];
        T res_im    = x.data.data[1];

        for (int i = 2; i < vector_size; i += 2)
        {
            res_re  += x.data.data[i + 0];
            res_im  += x.data.data[i + 1];
        }

        return compl_type(res_re, res_im);
    };
};

}}}
