#pragma once
#include "streamline/memory/unique_ptr.fwd.hpp"
#include "streamline/memory/impl/unique_ptr_base.hpp"

#include "streamline/metaprogramming/type_traits/supported_operations.hpp"
#include "streamline/numeric/int.hpp"


namespace sl::generic {
	template<typename T, typename DeleterT>
	class unique_ptr<T, DeleterT> : public impl::unique_ptr_base<T, DeleterT, unique_ptr<T, DeleterT>> {
	public:
		using base_type = impl::unique_ptr_base<T, DeleterT, unique_ptr<T, DeleterT>>;
	public:
		using typename base_type::pointer_type;
		using typename base_type::element_type;
		using typename base_type::value_type;
		using typename base_type::deleter_type;
		
	public:
		using base_type::base_type;
		using base_type::operator=;
	
	public:
		constexpr sl::add_lvalue_reference_t<T> operator*() const
		noexcept(requires(pointer_type p){{*p} noexcept;})
		requires(requires(pointer_type p){{*p}; });

		constexpr pointer_type operator->() const noexcept;
	};
}


namespace sl::generic {
	template<sl::traits::raw_array T, typename DeleterT>
	class unique_ptr<T, DeleterT> : public impl::unique_ptr_base<T, DeleterT, unique_ptr<T, DeleterT>> {
	public:
		using base_type = impl::unique_ptr_base<T, DeleterT, unique_ptr<T, DeleterT>>;
	public:
		using typename base_type::pointer_type;
		using typename base_type::element_type;
		using typename base_type::value_type;
		using typename base_type::deleter_type;
		
	public:
		using base_type::base_type;
		using base_type::operator=;
	
	public:
		constexpr sl::add_lvalue_reference_t<sl::remove_extent_t<T>> operator[](sl::index_t i) const
		noexcept(requires(pointer_type p){{p[i]} noexcept;})
		requires(requires(pointer_type p){{p[i]}; });
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


constexpr sl::unique_ptr<int> boing{nullptr};
// constexpr sl::unique_ptr<unsigned int> boing2{boing};
constexpr int* iasdasd = boing.get();

//constexpr sl::virtual_unique_ptr<int> v_boing{nullptr};
//constexpr sl::virtual_unique_ptr<unsigned int[]> v_boing2{boing};
//constexpr int* awqe = v_boing.get();