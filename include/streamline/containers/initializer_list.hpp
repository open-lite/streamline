#pragma once


#if !defined(_INITIALIZER_LIST) && !defined(_LIBCPP_INITIALIZER_LIST)

#include "streamline/numeric/int.hpp"


namespace std {
	template<typename T>
	struct initializer_list {
	public:
		using value_type      = T;
		using size_type       = sl::size_t;
		using index_type      = sl::index_t;
		
		using pointer_type                 = T const*;
		using const_pointer_type           = T const*;
		using reference_type               = value_type const&;
		using const_reference_type         = value_type const&;
		using iterator_type                = value_type const*;
		using const_iterator_type          = value_type const*;
		using reverse_iterator_type        = void; //TODO
		using const_reverse_iterator_type  = void; //TODO
	public:
		using pointer                 = pointer_type;
		using const_pointer           = const_pointer_type;
		using reference               = reference_type;
		using const_reference         = const_reference_type;
		using iterator                = iterator_type;
		using const_iterator          = const_iterator_type;
		using reverse_iterator        = reverse_iterator_type;
		using const_reverse_iterator  = const_reverse_iterator_type;

	public:
		iterator_type		_ptr;
		size_type			_size;

	private:
		constexpr initializer_list(const_iterator_type p, size_type s) noexcept : _ptr(p), _size(s) {}
	public:
		constexpr initializer_list() noexcept : _ptr(nullptr), _size(0) {}

	//Element access
	public:
		constexpr const_reference_type at(index_type pos) const noexcept;

		constexpr const_reference_type operator[](index_type pos) const noexcept;

		
		constexpr const_reference_type front() const noexcept;

		constexpr const_reference_type back() const noexcept;

		constexpr const_pointer_type data() const noexcept;


	//Iterators
	public:
		constexpr const_iterator_type  begin() const noexcept;
		constexpr const_iterator_type cbegin() const noexcept;

		constexpr const_iterator_type  end() const noexcept;
		constexpr const_iterator_type cend() const noexcept;


		constexpr const_reverse_iterator_type  rbegin() const noexcept;
		constexpr const_reverse_iterator_type crbegin() const noexcept;

		constexpr const_reverse_iterator_type  rend() const noexcept;
		constexpr const_reverse_iterator_type crend() const noexcept;


	//Capacity
	public:
		constexpr bool is_empty() const noexcept;
		constexpr bool empty() const noexcept;
		
		constexpr size_type size() const noexcept;
		//constexpr size_type max_size() const noexcept; //TODO
	};
}

//TODO
namespace std {
	template<typename T> constexpr typename initializer_list<T>::const_pointer_type data(initializer_list<T>) noexcept;


	template<typename T> constexpr typename initializer_list<T>::const_iterator_type  begin(initializer_list<T>) noexcept;
	template<typename T> constexpr typename initializer_list<T>::const_iterator_type cbegin(initializer_list<T>) noexcept;
	template<typename T> constexpr typename initializer_list<T>::const_iterator_type  end(initializer_list<T>) noexcept;
	template<typename T> constexpr typename initializer_list<T>::const_iterator_type cend(initializer_list<T>) noexcept;

	template<typename T> constexpr typename initializer_list<T>::const_reverse_iterator_type  rbegin(initializer_list<T>) noexcept;
	template<typename T> constexpr typename initializer_list<T>::const_reverse_iterator_type crbegin(initializer_list<T>) noexcept;
	template<typename T> constexpr typename initializer_list<T>::const_reverse_iterator_type  rend(initializer_list<T>) noexcept;
	template<typename T> constexpr typename initializer_list<T>::const_reverse_iterator_type crend(initializer_list<T>) noexcept;


	template<typename T> constexpr bool empty(initializer_list<T>) noexcept;	
}

#include "streamline/containers/initializer_list.inl"
#else
#include <initializer_list>
#endif

#include "streamline/metaprogramming/container_traits.fwd.hpp"


namespace sl {
	using std::initializer_list;

	
	using std::data;
	
	using std::begin;
	using std::cbegin;
	using std::end;
	using std::cend;
	using std::rbegin;
	using std::crbegin;
	using std::rend;
	using std::crend;
	
	using std::empty;
}

namespace sl {
	template<typename T>
	struct container_traits<initializer_list<T>> {
		constexpr static size_t size = dynamic_extent;
		constexpr static size_t size_bytes = dynamic_extent;
	};
}
