#pragma once
#include "streamline/functional/functor/comparison.hpp"
#include "streamline/metaprogramming/common_type.hpp"
#include "streamline/containers/initializer_list.hpp"


namespace sl::algo {
	template<typename ForwardIt, typename Compare = functor::less>
	constexpr ForwardIt max_element(ForwardIt first, ForwardIt last, Compare comp = {})
	noexcept(noexcept(comp(*last, *first)))
	requires requires { comp(*last, *first); } {
		if (first == last) return last;
		
		ForwardIt ret = first;
		while(++first != last)
		    if (comp(*ret, *first))
		        ret = first;
		return ret;
	}


	template<typename ForwardIt, typename Compare = functor::less>
	constexpr ForwardIt min_element(ForwardIt first, ForwardIt last, Compare comp = {})
	noexcept(noexcept(comp(*last, *first)))
	requires requires { comp(*last, *first); } {
		if (first == last) return last;
		
		ForwardIt ret = first;
		while(++first != last)
		    if (comp(*first, *ret))
		        ret = first;
		return ret;
	}
}




namespace sl::algo {
	template<typename L, typename R, typename Compare = functor::less>
	constexpr decltype(auto) max(L&& lhs, R&& rhs, Compare comp = {}) 
	noexcept(noexcept(comp(lhs, rhs)))
	requires requires { comp(lhs, rhs); } {
		return (comp(lhs, rhs)) ? forward<R>(rhs) : forward<L>(lhs);
	}


	template<typename T, typename Compare = functor::less>
	constexpr T max(initializer_list<T> il, Compare comp = {}) 
	noexcept(noexcept(max_element(il.begin(), il.end(), comp))) {
		return *max_element(il.begin(), il.end(), comp);
	}
}

namespace sl::algo {
	template<typename L, typename R, typename Compare = functor::less>
	constexpr decltype(auto) min(L&& lhs, R&& rhs, Compare comp = {}) 
	noexcept(noexcept(comp(lhs, rhs)))
	requires requires { comp(lhs, rhs); } {
		return (comp(lhs, rhs)) ? forward<L>(lhs) : forward<R>(rhs);
	}

	
	template<typename T, typename Compare = functor::less>
	constexpr T min(initializer_list<T> il, Compare comp = {}) 
	noexcept(noexcept(min_element(il.begin(), il.end(), comp))) {
		return *min_element(il.begin(), il.end(), comp);
	}
}