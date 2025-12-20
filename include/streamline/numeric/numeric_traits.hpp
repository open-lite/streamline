#pragma once
#include "streamline/numeric/impl/numeric_traits_base.hpp"


namespace sl {
	template<typename T>
	struct numeric_traits;
}


//bool
namespace sl {
	template<>
	struct numeric_traits<bool> : impl::numeric_traits_base<bool> {
		using type = bool;
	public:
		constexpr static type min = false;
		constexpr static type max = true;
	};
}


//integrals
namespace sl {
	template<>
	struct numeric_traits<signed char> : impl::numeric_traits_base<signed char> {
		using type = signed char;
	public:
		constexpr static type min = SCHAR_MIN;
		constexpr static type max = SCHAR_MAX;
	};

	template<>
	struct numeric_traits<unsigned char> : impl::numeric_traits_base<unsigned char> {
		using type = unsigned char;
	public:
		constexpr static type min = 0;
		constexpr static type max = UCHAR_MAX;
	};


	template<>
	struct numeric_traits<short> : impl::numeric_traits_base<short> {
		using type = short;
	public:
		constexpr static type min = SHRT_MIN;
		constexpr static type max = SHRT_MAX;
	};

	template<>
	struct numeric_traits<unsigned short> : impl::numeric_traits_base<unsigned short> {
		using type = unsigned short;
	public:
		constexpr static type min = 0;
		constexpr static type max = USHRT_MAX;
	};


	template<>
	struct numeric_traits<int> : impl::numeric_traits_base<int> {
		using type = int;
	public:
		constexpr static type min = INT_MIN;
		constexpr static type max = INT_MAX;
	};

	template<>
	struct numeric_traits<unsigned int> : impl::numeric_traits_base<unsigned int> {
		using type = unsigned int;
	public:
		constexpr static type min = 0;
		constexpr static type max = UINT_MAX;
	};


	template<>
	struct numeric_traits<long> : impl::numeric_traits_base<long> {
		using type = long;
	public:
		constexpr static type min = LONG_MIN;
		constexpr static type max = LONG_MAX;
	};

	template<>
	struct numeric_traits<unsigned long> : impl::numeric_traits_base<unsigned long> {
		using type = unsigned long;
	public:
		constexpr static type min = 0;
		constexpr static type max = ULONG_MAX;
	};


	template<>
	struct numeric_traits<long long> : impl::numeric_traits_base<long long> {
		using type = long long;
	public:
		constexpr static type min = LLONG_MIN;
		constexpr static type max = LLONG_MAX;
	};

	template<>
	struct numeric_traits<unsigned long long> : impl::numeric_traits_base<unsigned long long> {
		using type = unsigned long long;
	public:
		constexpr static type min = 0;
		constexpr static type max = ULLONG_MAX;
	};
}


//characters
namespace sl {
	template<>
	struct numeric_traits<char> : impl::numeric_traits_base<char> {
		using type = char;
	public:
		constexpr static type min = CHAR_MIN;
		constexpr static type max = CHAR_MAX;
	};


	template<>
	struct numeric_traits<wchar_t> : impl::numeric_traits_base<wchar_t> {
		using type = wchar_t;
	public:
		constexpr static type min = WCHAR_MIN;
		constexpr static type max = WCHAR_MAX;
	};


	template<>
	struct numeric_traits<char8_t> : impl::numeric_traits_base<char8_t> {
		using type = char8_t;
	public:
		constexpr static type min = 0;
		constexpr static type max = UCHAR_MAX;
	};


	template<>
	struct numeric_traits<char16_t> : impl::numeric_traits_base<char16_t> {
		using type = char16_t;
	public:
		constexpr static type min = 0;
		constexpr static type max = UINT_LEAST16_MAX;
	};
	

	template<>
	struct numeric_traits<char32_t> : impl::numeric_traits_base<char32_t> {
		using type = char32_t;
	public:
		constexpr static type min = 0;
		constexpr static type max = UINT_LEAST32_MAX;
	};
}



//floating points
namespace sl {

}