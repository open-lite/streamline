#pragma once
#include "streamline/memory/impl/unique_ptr_base.hpp"

#include "streamline/functional/invoke.hpp"
#include "streamline/universal/swap.hpp"


namespace sl::impl {
	template<typename T, typename DeleterT, typename DerivedT>
	constexpr unique_ptr_base<T, DeleterT, DerivedT>::unique_ptr_base()
	noexcept(traits::is_noexcept_default_constructible_v<deleter_type>)
	requires(traits::is_default_constructible_v<deleter_type>) :
		ptr{}, deleter{} {}

	template<typename T, typename DeleterT, typename DerivedT>
	constexpr unique_ptr_base<T, DeleterT, DerivedT>::unique_ptr_base(nullptr_t)
	noexcept(traits::is_noexcept_default_constructible_v<deleter_type>)
	requires(traits::is_default_constructible_v<deleter_type>) : 
		ptr{}, deleter{} {}


	template<typename T, typename DeleterT, typename DerivedT>
	template<typename U>
	constexpr unique_ptr_base<T, DeleterT, DerivedT>::unique_ptr_base(U p)
	noexcept(
		sl::traits::is_noexcept_constructible_from_v<pointer_type, U> &&
		sl::traits::is_noexcept_default_constructible_v<deleter_type>
	)
	requires(
		sl::traits::is_constructible_from_v<pointer_type, U> &&
		sl::traits::is_default_constructible_v<deleter_type> &&
		!sl::traits::is_pointer_v<deleter_type> && 
		is_convertible_to_array_pointer_type<U>
	) : 
		ptr{p}, deleter{} {}


	template<typename T, typename DeleterT, typename DerivedT>
	template<typename U, typename D>
	constexpr unique_ptr_base<T, DeleterT, DerivedT>::unique_ptr_base(U p, D&& d)
	noexcept(
		sl::traits::is_noexcept_constructible_from_v<pointer_type, U> &&
		sl::traits::is_forwarded_noexcept_constructible_from_v<deleter_type, D>
	)
	requires(
		sl::traits::is_constructible_from_v<pointer_type, U> &&
		sl::traits::is_forwarded_constructible_from_v<deleter_type, D> && 
		is_convertible_to_array_pointer_type<U>
	) :
		ptr{p}, deleter(::sl::forward<D>(d))
	{
		static_assert(
			!traits::is_rvalue_reference_v<D> ||
			!(traits::is_lvalue_reference_v<deleter_type> && traits::is_const_qualified_v<sl::remove_reference_t<deleter_type>>),
			"cannot initialize a const lvalue reference deleter with an rvalue reference"
		);
	}
}

namespace sl::impl {
	template<typename T, typename DeleterT, typename DerivedT>
	template<typename U, typename E>
	constexpr unique_ptr_base<T, DeleterT, DerivedT>::unique_ptr_base(unique_ptr_base<U, E, DerivedT>&& other)
	noexcept(
		is_noexcept_compatible<U, E> &&
		sl::traits::is_forwarded_noexcept_constructible_from_v<deleter_type, E>
	)
	requires(
		is_compatible<U, E> &&
		sl::traits::is_forwarded_constructible_from_v<deleter_type, E>
	) :
		ptr{other.release()}, deleter(::sl::forward<E>(other.deleter))
	{
		other.ptr = nullptr;
	}


	template<typename T, typename DeleterT, typename DerivedT>
	constexpr unique_ptr_base<T, DeleterT, DerivedT>::unique_ptr_base(unique_ptr_base&& other)
	noexcept(sl::traits::is_noexcept_move_constructible_v<deleter_type>)
	requires(sl::traits::is_move_constructible_v<deleter_type>) 
		: ptr{other.release()}, deleter(::sl::forward<deleter_type>(other.deleter))
	{
		other.ptr = nullptr;
	}
}

namespace sl::impl {
	template<typename T, typename DeleterT, typename DerivedT>
	constexpr unique_ptr_base<T, DeleterT, DerivedT>::~unique_ptr_base() noexcept {
		static_cast<DerivedT&>(*this).reset();
	}
}



namespace sl::impl {
	template<typename T, typename DeleterT, typename DerivedT>
	constexpr unique_ptr_base<T, DeleterT, DerivedT>& unique_ptr_base<T, DeleterT, DerivedT>::operator=(nullptr_t) noexcept {
		static_cast<DerivedT&>(*this).reset();
		return *this;
	}
}


namespace sl::impl {
	template<typename T, typename DeleterT, typename DerivedT>
	constexpr unique_ptr_base<T, DeleterT, DerivedT>& unique_ptr_base<T, DeleterT, DerivedT>::operator=(unique_ptr_base&& other)
	noexcept(sl::traits::is_forwarded_noexcept_assignable_from_v<deleter_type, deleter_type>)
	requires(sl::traits::is_forwarded_assignable_from_v<deleter_type, deleter_type>) {
		reset(other.release(), ::sl::forward<deleter_type>(other.deleter));
		return *this;
	}

	template<typename T, typename DeleterT, typename DerivedT>
	template<typename U, typename E>
	constexpr unique_ptr_base<T, DeleterT, DerivedT>& unique_ptr_base<T, DeleterT, DerivedT>::operator=(unique_ptr_base<U, E, DerivedT>&& other)
	noexcept(
		is_noexcept_compatible<U, E> &&
		sl::traits::is_forwarded_noexcept_assignable_from_v<deleter_type, E>
	)
	requires(
		is_compatible<U, E> &&
		sl::traits::is_forwarded_assignable_from_v<deleter_type, E>
	) {
		reset(other.release(), ::sl::forward<E>(other.deleter));
		return *this;
	}
}


namespace sl::impl {
	template<typename T, typename DeleterT, typename DerivedT>
	template<typename U>
	constexpr void unique_ptr_base<T, DeleterT, DerivedT>::reset(U p) noexcept 
	requires(sl::traits::is_assignable_from_v<pointer_type, U>) {
		const pointer_type old_ptr = this->ptr;
		this->ptr = p;
		if(old_ptr) {
			::sl::invoke_r<void>(this->deleter, sl::move(old_ptr));
			deleter.clear();
		}
	}

	template<typename T, typename DeleterT, typename DerivedT>
	template<typename U, typename D>
	constexpr void unique_ptr_base<T, DeleterT, DerivedT>::reset(U p, D&& d) noexcept  
	requires(
		sl::traits::is_assignable_from_v<pointer_type, U> &&
		sl::traits::is_forwarded_constructible_from_v<deleter_type, D>
	) {
		static_cast<DerivedT&>(*this).reset(p);
		deleter = ::sl::forward<D>(d);
	}


	template<typename T, typename DeleterT, typename DerivedT>
	constexpr typename unique_ptr_base<T, DeleterT, DerivedT>::pointer_type unique_ptr_base<T, DeleterT, DerivedT>::release() noexcept {
		const pointer_type temp = ptr;
		ptr = nullptr;
		return temp;
	}
	

	template<typename T, typename DeleterT, typename DerivedT>
	constexpr void unique_ptr_base<T, DeleterT, DerivedT>::swap(unique_ptr_base& other) noexcept {
		::sl::universal::swap(ptr, other.ptr);
		::sl::universal::swap(deleter, other.deleter);
	}
}

namespace sl::impl {
	template<typename T, typename DeleterT, typename DerivedT>
	constexpr auto&& unique_ptr_base<T, DeleterT, DerivedT>::get(this auto&& self) noexcept {
		return ::sl::forward_like<decltype(self)>(self.ptr);
	}

	template<typename T, typename DeleterT, typename DerivedT>
	template<index_t I>
	constexpr typename unique_ptr_base<T, DeleterT, DerivedT>::pointer_type
		unique_ptr_base<T, DeleterT, DerivedT>::
	get(index_constant_type<I>) noexcept {
		return &ptr[I];
	}

	template<typename T, typename DeleterT, typename DerivedT>
	constexpr auto&& unique_ptr_base<T, DeleterT, DerivedT>::get_deleter(this auto&& self) noexcept {
		static_assert(!traits::is_same_as_v<DeleterT, void>, 
			"get_deleter() not available for smart pointers with virtual deleters (since RTTI is always disabled). "
			"Use get_deleter_static() instead."
		);
		return ::sl::forward_like<decltype(self)>(self.deleter.get_deleter());
	}

	template<typename T, typename DeleterT, typename DerivedT>
	template<typename Deleter>
	constexpr Deleter* unique_ptr_base<T, DeleterT, DerivedT>::get_deleter_static() noexcept {
		return this->deleter.get_deleter_static();
	}

	template<typename T, typename DeleterT, typename DerivedT>
	constexpr unique_ptr_base<T, DeleterT, DerivedT>::operator bool() const noexcept {
		return get() != nullptr;
	}
}

namespace sl::impl {
	template<typename T, typename DeleterT, typename DerivedT>
	constexpr unique_ptr_base<T, DeleterT, DerivedT>::operator reference_pointer_type() const noexcept {
		return {get()};
	}

	template<typename T, typename DeleterT, typename DerivedT>
	constexpr unique_ptr_base<T, DeleterT, DerivedT>::operator reference_const_pointer_type() const noexcept {
		return {get()};
	}
}
