#pragma once
#include "streamline/metaprogramming/integer_sequence.hpp"
#include "streamline/metaprogramming/integral_constant.hpp"
#include "streamline/metaprogramming/forward.hpp"
#include "streamline/numeric/int.hpp"


namespace sl::impl {
	template<index_t I, typename T>
	struct tuple_element {
		[[no_unique_address]] T value;
	
	public:
		//TODO: figure out how to do this with explicit object parameters
		template<typename Self>
		constexpr auto&& operator[](this Self&& self, index_constant_type<I>) noexcept { 
			return static_cast<copy_cvref_t<Self, tuple_element<I, T>>>(self).value;
		}

		//constexpr T      &  operator[](index_constant_type<I>)      &  noexcept { return static_cast<tuple_element*>(this)->value; }
		//constexpr T const&  operator[](index_constant_type<I>) const&  noexcept { return static_cast<tuple_element*>(this)->value; }
		//constexpr T      && operator[](index_constant_type<I>)      && noexcept { return move(static_cast<tuple_element*>(this)->value); }
		//constexpr T const&& operator[](index_constant_type<I>) const&& noexcept { return move(static_cast<tuple_element*>(this)->value); }
	};
}
