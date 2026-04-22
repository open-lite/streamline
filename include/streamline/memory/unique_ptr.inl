#pragma once
#include "streamline/memory/unique_ptr.hpp"

#include "streamline/functional/invoke.hpp"
#include "streamline/universal/swap.hpp"


namespace sl::generic {
	template<typename T, typename DeleterT>
	constexpr add_lvalue_reference_t<T> unique_ptr<T, DeleterT>::operator*() const
	noexcept(requires(pointer_type p){{*p} noexcept;})
	requires(requires(pointer_type p){{*p}; }) {
		static_assert(
			!traits::does_reference_convert_from_temporary_v<add_lvalue_reference_t<T>, decltype(*::sl::declval<pointer_type>())>,
			"cannot convert dereferenced type to lvalue of type T"
		);
		return *this->get();
	}

	template<typename T, typename DeleterT>
	constexpr typename unique_ptr<T, DeleterT>::pointer_type unique_ptr<T, DeleterT>::operator->() const noexcept {
		return this->get();
	}
}


namespace sl::generic {
	template<sl::traits::raw_array T, typename DeleterT>
	constexpr sl::add_lvalue_reference_t<sl::remove_extent_t<T>> unique_ptr<T, DeleterT>::operator[](sl::index_t i) const
	noexcept(requires(pointer_type p){{p[i]} noexcept;})
	requires(requires(pointer_type p){{p[i]}; }) {
		return this->get()[i];
	}
}