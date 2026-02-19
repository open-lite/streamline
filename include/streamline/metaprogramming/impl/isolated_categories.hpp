#pragma once
#include "streamline/metaprogramming/constant.hpp"


namespace sl::impl {
	template<typename T> 
	struct is_integer : false_constant_type {};

	template<> struct is_integer<  signed char> : true_constant_type {};
	template<> struct is_integer<unsigned char> : true_constant_type {};
	template<> struct is_integer<  signed short> : true_constant_type {};
	template<> struct is_integer<unsigned short> : true_constant_type {};
	template<> struct is_integer<  signed int> : true_constant_type {};
	template<> struct is_integer<unsigned int> : true_constant_type {};
	template<> struct is_integer<  signed long> : true_constant_type {};
	template<> struct is_integer<unsigned long> : true_constant_type {};
	template<> struct is_integer<  signed long long> : true_constant_type {};
	template<> struct is_integer<unsigned long long> : true_constant_type {};

	#if defined(__SIZEOF_INT128__) && defined(__STRICT_ANSI__)
	template<> struct is_integer<  signed __int128> : true_constant_type {};
	template<> struct is_integer<unsigned __int128> : true_constant_type {};
	#endif
}

namespace sl::impl {
	template<typename T> 
	struct is_character : false_constant_type {};

	template<> struct is_character<char> : true_constant_type {};
	template<> struct is_character<wchar_t> : true_constant_type {};
	template<> struct is_character<char8_t> : true_constant_type {};
	template<> struct is_character<char16_t> : true_constant_type {};
	template<> struct is_character<char32_t> : true_constant_type {};
}


namespace sl::impl {
	template<typename T> 
	struct is_floating_point : false_constant_type {};

	template<> struct is_floating_point<float> : true_constant_type {};
	template<> struct is_floating_point<double> : true_constant_type {};
	template<> struct is_floating_point<long double> : true_constant_type {};

	#if defined(__STDCPP_FLOAT16_T__)
	template<> struct is_floating_point<_Float16> : true_constant_type {};
	#endif
	#if defined(__STDCPP_FLOAT32_T__)
	template<> struct is_floating_point<_Float32> : true_constant_type {};
	#endif
	#if defined(__STDCPP_FLOAT64_T__)
	template<> struct is_floating_point<_Float64> : true_constant_type {};
	#endif
	#if defined(__STDCPP_FLOAT128_T__)
	template<> struct is_floating_point<_Float128> : true_constant_type {};
	#endif
	#if defined(__STDCPP_BFLOAT16_T__)
	template<> struct is_floating_point<__gnu_cxx::__bfloat16_t> : true_constant_type {};
	#endif
}