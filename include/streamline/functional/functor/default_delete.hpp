#pragma once
#include "streamline/memory/delete.hpp"
#include "streamline/metaprogramming/type_traits/relationships.hpp"

namespace sl::functor {
	template<typename T>
	struct default_delete {
		constexpr default_delete() noexcept = default;

		template<typename U>
		constexpr default_delete(default_delete<U> const&) 
		noexcept(sl::traits::is_noexcept_convertible_to_v<U*, T*>)
		requires(sl::traits::is_convertible_to_v<U*, T*>) {}

	public:
		constexpr void operator()(T* ptr) const noexcept {
			static_assert(!traits::is_same_as_v<remove_cvref_t<T>, void>, "cannot delete (possibly cv-qualified) pointer to void");
			static_assert(sizeof(T) > 0, "cannot delete pointer to incomplete type");

			delete ptr;
		};
	};
}

namespace sl::functor {
	template<typename T>
	struct default_delete<T[]> {
		constexpr default_delete() noexcept = default;

		template<typename U>
		constexpr default_delete(default_delete<U[]> const&) 
		noexcept(sl::traits::is_noexcept_convertible_to_v<U(*)[], T(*)[]>)
		requires(sl::traits::is_convertible_to_v<U(*)[], T(*)[]>) {}

	public:
		template<typename U>
		constexpr void operator()(U* ptr) const 
		noexcept(sl::traits::is_noexcept_convertible_to_v<U(*)[], T(*)[]>)
		requires(sl::traits::is_convertible_to_v<U(*)[], T(*)[]>) {
			static_assert(!traits::is_same_as_v<remove_cvref_t<T>, void>, "cannot delete (possibly cv-qualified) pointer to void");
			static_assert(sizeof(U) > 0 && sizeof(T) > 0, "cannot delete pointer to incomplete type");
			delete[] ptr;
		};
	};
}