#pragma once
#include "streamline/metaprogramming/constant.hpp"
#include "streamline/metaprogramming/type_traits/isolated_categories.hpp"


namespace sl::impl {
    template<typename T, bool Constraints>
    struct is_signed : false_constant_type {};
 
    template<typename T>
    struct is_signed<T, true> : bool_constant_type<T(-1) < T(0)> {};


    template<typename T, bool Constraints>
    struct is_unsigned : false_constant_type {};
 
    template<typename T>
    struct is_unsigned<T, true> : bool_constant_type<T(0) < T(-1)> {};
}