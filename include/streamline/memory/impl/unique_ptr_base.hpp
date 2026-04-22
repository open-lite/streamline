#pragma once
#include "streamline/memory/impl/deleter_wrapper.hpp"
#include "streamline/memory/reference_ptr.hpp"
#include "streamline/metaprogramming/type_traits/relationships.hpp"
#include "streamline/metaprogramming/type_modifiers.hpp"
#include "streamline/metaprogramming/type_traits/supported_operations.hpp"


namespace sl::impl {
	template<typename T, typename DeleterT, typename DerivedT>
	class unique_ptr_base {
	public:
		using pointer_type = sl::remove_extent_t<T>*;
		using element_type = sl::remove_extent_t<T>;
		using value_type = sl::remove_extent_t<T>*;
		using deleter_type = deleter_wrapper<pointer_type, DeleterT>;
	public:
		using reference_pointer_type = sl::reference_ptr<T>;
		using reference_const_pointer_type = sl::reference_ptr<const T>;
	public:
		using pointer = sl::remove_extent_t<T>*;

	protected:
		template<typename U>
		inline constexpr static bool is_convertible_to_array_pointer_type = (
			(!sl::traits::is_raw_array_v<U>) ||
			(sl::traits::is_pointer_v<U> && sl::traits::is_convertible_to_v<sl::remove_pointer_t<U>(*)[], element_type(*)[]>)
		);

		template<typename U, typename E>
		inline constexpr static bool is_compatible = (
			(!sl::traits::is_raw_array_v<U> && sl::traits::is_convertible_to_v<typename unique_ptr_base<U, E, DerivedT>::pointer_type, pointer_type>) ||
			(sl::traits::is_raw_array_v<U> && sl::traits::is_convertible_to_v<typename unique_ptr_base<U, E, DerivedT>::element_type(*)[], element_type(*)[]>)
		);
		template<typename U, typename E>
		inline constexpr static bool is_noexcept_compatible = (
			(!sl::traits::is_raw_array_v<U> && sl::traits::is_noexcept_convertible_to_v<typename unique_ptr_base<U, E, DerivedT>::pointer_type, pointer_type>) ||
			(sl::traits::is_raw_array_v<U> && sl::traits::is_noexcept_convertible_to_v<typename unique_ptr_base<U, E, DerivedT>::element_type(*)[], element_type(*)[]>)
		);

		
	public:
		constexpr unique_ptr_base()
		noexcept(sl::traits::is_noexcept_default_constructible_v<deleter_type>)
		requires(sl::traits::is_default_constructible_v<deleter_type>);

		constexpr unique_ptr_base(nullptr_t)
		noexcept(sl::traits::is_noexcept_default_constructible_v<deleter_type>)
		requires(sl::traits::is_default_constructible_v<deleter_type>);

	public:
		template<typename U>
		constexpr explicit unique_ptr_base(U p) 
		noexcept(
			sl::traits::is_noexcept_constructible_from_v<pointer_type, U> &&
			sl::traits::is_noexcept_default_constructible_v<deleter_type>
		)
		requires(
			sl::traits::is_constructible_from_v<pointer_type, U> &&
			sl::traits::is_default_constructible_v<deleter_type> &&
			!sl::traits::is_pointer_v<deleter_type> && 
			is_convertible_to_array_pointer_type<U>
		);

		
		template<typename U, typename D>
		constexpr unique_ptr_base(U p, D&& d)
		noexcept(
			sl::traits::is_noexcept_constructible_from_v<pointer_type, U> &&
			sl::traits::is_forwarded_noexcept_constructible_from_v<deleter_type, D>
		)
		requires(
			sl::traits::is_constructible_from_v<pointer_type, U> &&
			sl::traits::is_forwarded_constructible_from_v<deleter_type, D> && 
			is_convertible_to_array_pointer_type<U>
		);

	public:
		template<typename U, typename E>
		constexpr unique_ptr_base(unique_ptr_base<U, E, DerivedT>&& other)
		noexcept(
			is_noexcept_compatible<U, E> &&
			sl::traits::is_forwarded_noexcept_constructible_from_v<deleter_type, E>
		)
		requires(
			is_compatible<U, E> &&
			sl::traits::is_forwarded_constructible_from_v<deleter_type, E>
		);
	public:
		constexpr unique_ptr_base(unique_ptr_base&& other)
		noexcept(sl::traits::is_noexcept_move_constructible_v<deleter_type>)
		requires(sl::traits::is_move_constructible_v<deleter_type>);


		constexpr unique_ptr_base(unique_ptr_base const&) noexcept = delete;
	
	public:
		constexpr ~unique_ptr_base() noexcept;


	public:
		constexpr unique_ptr_base& operator=(nullptr_t) noexcept;

	public:
		constexpr unique_ptr_base& operator=(unique_ptr_base&&)
		noexcept(sl::traits::is_forwarded_noexcept_assignable_from_v<deleter_type, deleter_type>)
		requires(sl::traits::is_forwarded_assignable_from_v<deleter_type, deleter_type>);

		template<typename U, typename E>
		constexpr unique_ptr_base& operator=(unique_ptr_base<U, E, DerivedT>&&)
		noexcept(
			is_noexcept_compatible<U, E> &&
			sl::traits::is_forwarded_noexcept_assignable_from_v<deleter_type, E>
		)
		requires(
			is_compatible<U, E> &&
			sl::traits::is_forwarded_assignable_from_v<deleter_type, E>
		);

		constexpr unique_ptr_base& operator=(unique_ptr_base const&) noexcept = delete;
		
	public:
		template<typename U = nullptr_t>
		constexpr void reset(U p = nullptr) noexcept 
		requires(sl::traits::is_assignable_from_v<pointer_type, U>);

		template<typename U, typename D>
		constexpr void reset(U p, D&& d) noexcept 
		requires(
			sl::traits::is_assignable_from_v<pointer_type, U> &&
			sl::traits::is_forwarded_constructible_from_v<deleter_type, D>
		);

		constexpr pointer_type release() noexcept;
		constexpr void swap(unique_ptr_base& other) noexcept;

	public:
		constexpr auto&& get(this auto&& self) noexcept;
		template<index_t I>
		constexpr pointer_type get(sl::index_constant_type<I>) noexcept;
		constexpr auto&& get_deleter(this auto&& self) noexcept;
		template<typename Deleter>
		constexpr Deleter* get_deleter_static() noexcept;
		constexpr explicit operator bool() const noexcept;

	public:
		constexpr operator reference_pointer_type() const noexcept;
		constexpr operator reference_const_pointer_type() const noexcept;

	protected:
		pointer_type ptr;
		[[no_unique_address]] deleter_type deleter;
	};
}


#include "streamline/memory/impl/unique_ptr_base.inl"
