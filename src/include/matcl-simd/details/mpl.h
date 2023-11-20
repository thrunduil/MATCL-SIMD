/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */


#pragma once

#include <type_traits>

namespace matcl { namespace details
{

template<bool cond,class T1,class T2> 
struct select_if                { using type = T1 ;};

template<class T1,class T2> 
struct select_if<false,T1,T2>   { using type = T2 ;};

//allow use always false conditions in static_assert 
template<class T>
struct dependent_false          { static const bool value = false; };

template<class... T>
struct dependent_false_var      { static const bool value = false; };

template<class T, T Val>
struct dependent_value_false    { static const bool value = false; };

// enablers
template<bool cond,class T> 
struct enable_if                { using type = T; };

template<class T>
struct enable_if<false,T>       {};

// template pack manipulation
template<size_t pos, class ... Args> 
struct get_type{};

template<class T0, class ... Args> 
struct get_type<0, T0, Args...>
{
    using type = T0;
};

template<size_t pos, class T0, class ... Args> 
struct get_type<pos, T0, Args...>
{
    using type = typename get_type<pos - 1, Args...>::type;
};

template<size_t pos, class ... Args> 
struct get_elem_impl{};

template<class S, class ... Args> 
struct get_elem_impl<0, S, Args...>
{
    static S eval(const S& x, const Args& ...)
    {
        return x;
    }
};

template<size_t pos, class S, class ... Args> 
struct get_elem_impl<pos, S, Args...>
{
    using Ret =  typename get_type<pos - 1, Args...>::type;
    static Ret eval(const S&, const Args& ... args)
    {
        return get_elem_impl<pos - 1, Args...>::eval(args...);
    }
};

template<size_t pos, class ... Args> 
auto get_elem(const Args& ... args) -> typename get_type<pos, Args...>::type
{
    return get_elem_impl<pos, Args...>::eval(args...);
};

};};