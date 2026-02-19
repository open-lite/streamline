#pragma once
#include "streamline/containers/array.hpp"
#include "streamline/diagnostics/terminate.hpp"
#include "streamline/algorithm/minmax.hpp"


//Element access
namespace sl {
	template<size_t N, typename T>
	constexpr auto&& generic_array<N, T>::at(this auto&& self, generic_array::index_type pos) noexcept {
		if(pos >= N) sl::terminate();
		return sl::forward<decltype(self)>(self)._data[pos];
	}
	
	template<size_t N, typename T>
	constexpr auto generic_array<N, T>::try_at(this auto&& self, generic_array::index_type pos) noexcept {
		//TODO
	}
	
	template<size_t N, typename T>
	constexpr auto&& generic_array<N, T>::operator[](this auto&& self, index_type pos) noexcept {
		return sl::forward<decltype(self)>(self)._data[pos];
	}
	
	
	template<size_t N, typename T>
	template<index_t I>
	constexpr auto&& generic_array<N, T>::get(this auto&& self) noexcept {
		return sl::forward<decltype(self)>(self)._data[I];
	}


	
	template<size_t N, typename T>
	constexpr auto&& generic_array<N, T>::front(this auto&& self) noexcept {
		return sl::forward<decltype(self)>(self)._data[0];
	}
	
	template<size_t N, typename T>
	constexpr auto&& generic_array<N, T>::back(this auto&& self) noexcept {
		return sl::forward<decltype(self)>(self)._data[N - 1];
	}


	template<size_t N, typename T>
	constexpr auto generic_array<N, T>::data(this auto&& self) noexcept {
		return sl::forward_as_lvalue<decltype(self)>(self)._data;
	}
}

//Iterators
namespace sl {
	template<size_t N, typename T>
	constexpr auto generic_array<N, T>::begin(this auto&& self) noexcept {
		return sl::forward_as_lvalue<decltype(self)>(self)._data;
	}

	
	template<size_t N, typename T>
	constexpr generic_array<N,T>::const_iterator_type generic_array<N, T>::cbegin(this auto const& self) noexcept {
		return self._data;
	}

	
	template<size_t N, typename T>
	constexpr auto generic_array<N, T>::end(this auto&& self) noexcept {
		return sl::forward_as_lvalue<decltype(self)>(self)._data + N;
	}

	template<size_t N, typename T>
	constexpr generic_array<N,T>::const_iterator_type generic_array<N, T>::cend(this auto const& self) noexcept {
		return self._data + N;
	}


	
	// template<size_t N, typename T>
	// template<typename Self>
	// constexpr auto generic_array<N, T>::rbegin(this auto&& self) noexcept {

	// }
	
	// template<size_t N, typename T>
	// template<typename Self>
	// constexpr generic_array<N,T>::const_reverse_iterator_type generic_array<N, T>::crbegin(this auto const& self) noexcept {

	// }

	
	// template<size_t N, typename T>
	// template<typename Self>
	// constexpr auto generic_array<N, T>::rend(this auto&& self) noexcept;
	
	// template<size_t N, typename T>
	// template<typename Self>
	// constexpr generic_array<N,T>::const_reverse_iterator_type generic_array<N, T>::crend(this auto const& self) noexcept {

	// }
}

//Capacity
namespace sl {
	template<size_t N, typename T>
	consteval bool generic_array<N, T>::is_empty() noexcept {
		return N == 0;
	}

	template<size_t N, typename T>
	consteval bool generic_array<N, T>::empty() noexcept {
		return N == 0;
	}


	template<size_t N, typename T>
	consteval generic_array<N, T>::size_type generic_array<N, T>::size() noexcept {
		return N;
	}

	template<size_t N, typename T>
	consteval generic_array<N, T>::size_type generic_array<N, T>::max_size() noexcept {
		return N;
	}


	template<size_t N, typename T>
	consteval generic_array<N, T>::size_type generic_array<N, T>::size_bytes() noexcept {
		return size() * sizeof(T);
	}

	template<size_t N, typename T>
	consteval generic_array<N, T>::size_type generic_array<N, T>::max_size_bytes() noexcept {
		return size() * sizeof(T);
	}
}

//Operations
namespace sl {

}

//Equality
namespace sl {
	
}
