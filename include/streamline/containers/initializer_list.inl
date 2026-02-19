#pragma once
#include "streamline/containers/initializer_list.hpp"

#include "streamline/diagnostics/terminate.hpp"


//Element access
namespace std {
	template<typename T>
	constexpr typename initializer_list<T>::const_reference_type
	initializer_list<T>::at(index_type pos) const noexcept {
		if(pos >= _size) sl::terminate();
		return _ptr[pos];
	}

	
	template<typename T>
	constexpr typename initializer_list<T>::const_reference_type
	initializer_list<T>::operator[](index_type pos) const noexcept {
		return _ptr[pos];
	}

	
	
	template<typename T>
	constexpr typename initializer_list<T>::const_reference_type
	initializer_list<T>::front() const noexcept {
		return _ptr[0];
	}

	
	template<typename T>
	constexpr typename initializer_list<T>::const_reference_type
	initializer_list<T>::back() const noexcept {
		return _ptr[_size - 1];
	}

	
	template<typename T>
	constexpr typename initializer_list<T>::const_pointer_type
	initializer_list<T>::data() const noexcept {
		return _ptr;
	}
}


//Iterators
namespace std {
	template<typename T>
	constexpr typename initializer_list<T>::const_iterator_type
	initializer_list<T>::begin() const noexcept {
		return _ptr;
	}

	template<typename T>
	constexpr typename initializer_list<T>::const_iterator_type
	initializer_list<T>::cbegin() const noexcept {
		return _ptr;
	}

	
	template<typename T>
	constexpr typename initializer_list<T>::const_iterator_type
	initializer_list<T>::end() const noexcept {
		return _ptr + _size;
	}

	template<typename T>
	constexpr typename initializer_list<T>::const_iterator_type
	initializer_list<T>::cend() const noexcept {
		return _ptr + _size;
	}

	
	
	template<typename T>
	constexpr typename initializer_list<T>::const_reverse_iterator_type
	initializer_list<T>::rbegin() const noexcept {
		//TODO
	}

	template<typename T>
	constexpr typename initializer_list<T>::const_reverse_iterator_type
	initializer_list<T>::crbegin() const noexcept {
		//TODO
	}

	
	template<typename T>
	constexpr typename initializer_list<T>::const_reverse_iterator_type
	initializer_list<T>::rend() const noexcept {
		//TODO
	}

	template<typename T>
	constexpr typename initializer_list<T>::const_reverse_iterator_type
	initializer_list<T>::crend() const noexcept {
		//TODO
	}

}


//Capacity
namespace std {
	template<typename T>
	constexpr bool 
	initializer_list<T>::is_empty() const noexcept {
		return _size == 0;
	}

	template<typename T>
	constexpr bool 
	initializer_list<T>::empty() const noexcept {
		return _size == 0;
	}


	template<typename T>
	constexpr typename initializer_list<T>::size_type 
	initializer_list<T>::size() const noexcept {
		return _size;
	}

}