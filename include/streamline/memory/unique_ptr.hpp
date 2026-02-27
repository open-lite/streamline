#pragma once
#include "streamline/memory/unique_ptr.fwd.hpp"

#include "streamline/metaprogramming/type_traits/supported_operations.hpp"
#include "streamline/numeric/int.hpp"


namespace sl::generic {
	template<typename T, sl::traits::noexcept_invocable_r<void, T*> DeleterT>
	class unique_ptr<T, DeleterT> {
	public:
		using pointer_type = T*;
		using element_type = T;
		using value_type = T*;
		using deleter_type = DeleterT;
	public:
		using pointer = T*;
		
	public:
		constexpr unique_ptr()
		noexcept(sl::traits::is_noexcept_default_constructible_v<DeleterT>)
		requires(sl::traits::is_default_constructible_v<DeleterT>);

		constexpr unique_ptr(nullptr_t)
		noexcept(sl::traits::is_noexcept_default_constructible_v<DeleterT>)
		requires(sl::traits::is_default_constructible_v<DeleterT>);


		constexpr explicit unique_ptr(pointer_type p) 
		noexcept(sl::traits::is_noexcept_default_constructible_v<DeleterT>)
		requires(
			sl::traits::is_default_constructible_v<DeleterT> && 
			!sl::traits::is_pointer_v<DeleterT>
		);

		
		template<typename D>
		constexpr unique_ptr(pointer_type p, D&& d)
		noexcept(sl::traits::is_forwarded_noexcept_constructible_from_v<DeleterT, D>)
		requires(sl::traits::is_forwarded_constructible_from_v<DeleterT, D>);

	public:
		template<typename U, typename E>
		constexpr unique_ptr(unique_ptr<U, E>&& other)
		noexcept(sl::traits::is_forwarded_noexcept_constructible_from_v<DeleterT, E>)
		requires(
			sl::traits::is_forwarded_constructible_from_v<DeleterT, E> &&
			sl::traits::is_convertible_to_v<pointer_type, typename unique_ptr<U, E>::pointer_type> &&
			sl::traits::is_raw_array_v<U> && 
			(
				(sl::traits::is_reference_v<DeleterT> && sl::traits::is_same_as_v<DeleterT, E>) ||
				(!sl::traits::is_reference_v<DeleterT> && sl::traits::is_convertible_to_v<E, DeleterT>)
			)
		);

		constexpr unique_ptr(unique_ptr const&) noexcept = delete;

	public:
		constexpr ~unique_ptr() noexcept;

	
	public:
		constexpr unique_ptr& operator=(nullptr_t) noexcept;

	public:
		template<typename U, typename E>
		constexpr unique_ptr& operator=(unique_ptr<U, E>&& other)
		noexcept(sl::traits::is_forwarded_noexcept_constructible_from_v<DeleterT, E>)
		requires(
			sl::traits::is_forwarded_constructible_from_v<DeleterT, E> &&
			sl::traits::is_convertible_to_v<pointer_type, typename unique_ptr<U, E>::pointer_type> &&
			sl::traits::is_raw_array_v<U> && 
			(
				(sl::traits::is_reference_v<DeleterT> && sl::traits::is_same_as_v<DeleterT, E>) ||
				(!sl::traits::is_reference_v<DeleterT> && sl::traits::is_convertible_to_v<E, DeleterT>)
			)
		);
		
		constexpr unique_ptr& operator=(unique_ptr const&) noexcept = delete;

	public:
		constexpr pointer_type release() noexcept;
		constexpr void reset(pointer_type p = pointer_type{}) noexcept;
		constexpr void swap(unique_ptr& other) noexcept;
	
	public:
		template<index_t I = 0>
		constexpr auto&& get(this auto&& self, sl::index_constant_type<I> = {}) noexcept;
		constexpr auto&& get_deleter(this auto&& self) noexcept;
		constexpr explicit operator bool() const noexcept;

		constexpr sl::add_lvalue_reference_t<T> operator*() const
		noexcept(requires(pointer_type p){{*p} noexcept;})
		requires(requires(pointer_type p){{*p}; });

		constexpr pointer_type operator->() const noexcept;

	private:
		T* ptr;
		[[no_unique_address]] DeleterT deleter;
	};
}

namespace sl::generic {
	template<typename T, sl::traits::noexcept_invocable_r<void, T*> DeleterT>
	class unique_ptr<T[], DeleterT> {
		static_assert(sl::traits::is_raw_array_v<T>, "unique_ptr<T[]> not yet implemented");
	};
}


namespace sl {
	//TODO
	//operator<=> and operator==

	
	//TODO
	//template<typename CharT, typename Traits, typename Y, typename D>
	//constexpr sl::basic_ostream<CharT, Traits>& operator<<(sl::basic_ostream<CharT, Traits>& os, const sl::unique_ptr<Y, D>& p);
}


#include "streamline/memory/unique_ptr.universal.inl"
#include "streamline/memory/unique_ptr.inl"


constexpr sl::unique_ptr<int> boing{};
constexpr int* iasdasd = boing.get();