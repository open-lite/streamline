#pragma once
#include "streamline/memory/unique_ptr.hpp"

#include "streamline/functional/invoke.hpp"
#include "streamline/universal/swap.hpp"


namespace sl::generic {
	template<typename T, traits::noexcept_invocable_r<void, T*> DeleterT>
	constexpr unique_ptr<T, DeleterT>::unique_ptr()
	noexcept(traits::is_noexcept_default_constructible_v<DeleterT>)
	requires(traits::is_default_constructible_v<DeleterT>) :
		ptr{}, deleter{} {}

	template<typename T, traits::noexcept_invocable_r<void, T*> DeleterT>
	constexpr unique_ptr<T, DeleterT>::unique_ptr(nullptr_t)
	noexcept(traits::is_noexcept_default_constructible_v<DeleterT>)
	requires(traits::is_default_constructible_v<DeleterT>) : 
		ptr{}, deleter{} {}


	template<typename T, traits::noexcept_invocable_r<void, T*> DeleterT>
	constexpr unique_ptr<T, DeleterT>::unique_ptr(pointer_type p) 
	noexcept(traits::is_noexcept_default_constructible_v<DeleterT>)
	requires(
		traits::is_default_constructible_v<DeleterT> && 
		!traits::is_pointer_v<DeleterT>
	) : 
		ptr{p}, deleter{} {}


	template<typename T, traits::noexcept_invocable_r<void, T*> DeleterT>
	template<typename D>
	constexpr unique_ptr<T, DeleterT>::unique_ptr(pointer_type p, D&& d)
	noexcept(traits::is_forwarded_noexcept_constructible_from_v<DeleterT, D>)
	requires(traits::is_forwarded_constructible_from_v<DeleterT, D>) :
		ptr{p}, deleter(::sl::forward<D>(d))
	{
		static_assert(
			!traits::is_rvalue_reference_v<D> ||
			!(traits::is_lvalue_reference_v<DeleterT> && traits::is_const_qualified_v<sl::remove_reference_t<DeleterT>>),
			"cannot initialize a const lvalue reference deleter with an rvalue reference"
		);
	}
}

namespace sl::generic {
	template<typename T, traits::noexcept_invocable_r<void, T*> DeleterT>
	template<typename U, typename E>
	constexpr unique_ptr<T, DeleterT>::unique_ptr(unique_ptr<U, E>&& other)
	noexcept(traits::is_forwarded_noexcept_constructible_from_v<DeleterT, E>)
	requires(
		traits::is_forwarded_constructible_from_v<DeleterT, E> &&
		traits::is_convertible_to_v<pointer_type, typename unique_ptr<U, E>::pointer_type> &&
		traits::is_raw_array_v<U> && 
		(
			(traits::is_reference_v<DeleterT> && traits::is_same_as_v<DeleterT, E>) ||
			(!traits::is_reference_v<DeleterT> && traits::is_convertible_to_v<E, DeleterT>)
		)
	) :
		ptr{other.release()}, deleter(::sl::forward<E>(other.deleter)) {}
}

namespace sl::generic {
	template<typename T, traits::noexcept_invocable_r<void, T*> DeleterT>
	constexpr unique_ptr<T, DeleterT>::~unique_ptr() noexcept {
		if(get() == nullptr) return;
		::sl::invoke_r<void>(get_deleter(), sl::move(get()));
	}
}


namespace sl::generic {
	template<typename T, traits::noexcept_invocable_r<void, T*> DeleterT>
	constexpr unique_ptr<T, DeleterT>& unique_ptr<T, DeleterT>::operator=(nullptr_t) noexcept {
		reset();
		return *this;
	}
}

namespace sl::generic {
	template<typename T, traits::noexcept_invocable_r<void, T*> DeleterT>
	template<typename U, typename E>
	constexpr unique_ptr<T, DeleterT>& unique_ptr<T, DeleterT>::operator=(unique_ptr<U, E>&& other)
	noexcept(traits::is_forwarded_noexcept_constructible_from_v<DeleterT, E>)
	requires(
		traits::is_forwarded_constructible_from_v<DeleterT, E> &&
		traits::is_convertible_to_v<pointer_type, typename unique_ptr<U, E>::pointer_type> &&
		traits::is_raw_array_v<U> && 
		(
			(traits::is_reference_v<DeleterT> && traits::is_same_as_v<DeleterT, E>) ||
			(!traits::is_reference_v<DeleterT> && traits::is_convertible_to_v<E, DeleterT>)
		)
	) {
		reset(other.release());
		deleter = ::sl::forward<E>(other.deleter);
		return *this;
	}
}


namespace sl::generic {
	template<typename T, traits::noexcept_invocable_r<void, T*> DeleterT>
	constexpr typename unique_ptr<T, DeleterT>::pointer_type unique_ptr<T, DeleterT>::release() noexcept {
		const pointer_type temp = ptr;
		ptr = nullptr;
		return temp;
	}

	template<typename T, traits::noexcept_invocable_r<void, T*> DeleterT>
	constexpr void unique_ptr<T, DeleterT>::reset(pointer_type p) noexcept {
		const pointer_type old_ptr = ptr;
		ptr = p;
		if(old_ptr)
			::sl::invoke_r<void>(get_deleter(), old_ptr);
	}

	template<typename T, traits::noexcept_invocable_r<void, T*> DeleterT>
	constexpr void unique_ptr<T, DeleterT>::swap(unique_ptr& other) noexcept {
		::sl::universal::swap(ptr, other.ptr);
		::sl::universal::swap(deleter, other.deleter);
	}
}

namespace sl::generic {
	template<typename T, traits::noexcept_invocable_r<void, T*> DeleterT>
	template<index_t I>
	constexpr auto&& unique_ptr<T, DeleterT>::get(this auto&& self, index_constant_type<I>) noexcept {
		return ::sl::forward_like<decltype(self)>(self.ptr);
	}

	template<typename T, traits::noexcept_invocable_r<void, T*> DeleterT>
	constexpr auto&& unique_ptr<T, DeleterT>::get_deleter(this auto&& self) noexcept {
		return ::sl::forward_like<decltype(self)>(self.deleter);
	}

	template<typename T, traits::noexcept_invocable_r<void, T*> DeleterT>
	constexpr unique_ptr<T, DeleterT>::operator bool() const noexcept {
		return get() != nullptr;
	}
}

namespace sl::generic {
	template<typename T, traits::noexcept_invocable_r<void, T*> DeleterT>
	constexpr add_lvalue_reference_t<T> unique_ptr<T, DeleterT>::operator*() const
	noexcept(requires(pointer_type p){{*p} noexcept;})
	requires(requires(pointer_type p){{*p}; }) {
		static_assert(
			!traits::does_reference_convert_from_temporary_v<add_lvalue_reference_t<T>, decltype(*::sl::declval<pointer_type>())>,
			"cannot convert dereferenced type to lvalue of type T"
		);
		return *get();
	}

	template<typename T, traits::noexcept_invocable_r<void, T*> DeleterT>
	constexpr typename unique_ptr<T, DeleterT>::pointer_type unique_ptr<T, DeleterT>::operator->() const noexcept {
		return get();
	}
}