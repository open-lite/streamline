#pragma once
#include "streamline/memory/reference_ptr.fwd.hpp"

#include "streamline/metaprogramming/constant.hpp"
#include "streamline/metaprogramming/forward.hpp"
#include "streamline/metaprogramming/type_modifiers.hpp"

namespace sl::generic {
	template<typename T>
	struct reference_ptr<T> {
	public:
		using pointer_type = sl::remove_extent_t<T>*;
		using element_type = sl::remove_extent_t<T>;
		using value_type = sl::remove_extent_t<T>*;
	
	public:
		constexpr sl::add_lvalue_reference_t<element_type> operator*() const
		noexcept(requires(pointer_type p){{*p} noexcept;})
		requires(requires(pointer_type p){{*p}; } && !sl::traits::is_raw_array_v<T>) {
			return *_ptr;
		}

		constexpr sl::add_lvalue_reference_t<element_type> operator[](sl::index_t i) const
		noexcept(requires(pointer_type p){{p[i]} noexcept;})
		requires(requires(pointer_type p){{p[i]}; } && sl::traits::is_raw_array_v<T>) {
			return _ptr[i];
		}

		constexpr pointer_type operator->() const noexcept 
		requires(!sl::traits::is_raw_array_v<T>) { 
			return _ptr; 
		}
		
	public:
		constexpr operator T*() const noexcept { return _ptr; }
		constexpr explicit operator bool() const noexcept { return _ptr != nullptr; }

		constexpr pointer_type get() const noexcept {
			return _ptr;
		}

		template<index_t I>
		constexpr pointer_type get(sl::index_constant_type<I>) const noexcept {
			return &_ptr[I];
		}

		constexpr operator reference_ptr<const T>() const noexcept {
			return {_ptr};
		}
	
	public:
		T* _ptr;
	};
}