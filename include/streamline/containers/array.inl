#pragma once
#include "streamline/containers/array.hpp"
#include "streamline/diagnostics/terminate.hpp"
#include "streamline/containers/impl/make_array.hpp"
#include "streamline/algorithm/minmax.hpp"


//Element access
namespace sl {
	template<size_t N, typename T>
	constexpr auto&& generic_array<N, T>::at(this auto&& self, generic_array::index_type pos) noexcept {
		if(pos >= N) terminate();
		return forward<decltype(self)>(self)._data[pos];
	}
	
	template<size_t N, typename T>
	constexpr auto generic_array<N, T>::try_at(this auto&& self, generic_array::index_type pos) noexcept {
		//TODO
	}
	
	template<size_t N, typename T>
	constexpr auto&& generic_array<N, T>::operator[](this auto&& self, index_type pos) noexcept {
		return forward<decltype(self)>(self)._data[pos];
	}
	
	
	template<size_t N, typename T>
	template<index_t I>
	constexpr auto&& generic_array<N, T>::get(this auto&& self) noexcept {
		return forward<decltype(self)>(self)._data[I];
	}


	
	template<size_t N, typename T>
	constexpr auto&& generic_array<N, T>::front(this auto&& self) noexcept {
		return forward<decltype(self)>(self)._data[0];
	}
	
	template<size_t N, typename T>
	constexpr auto&& generic_array<N, T>::back(this auto&& self) noexcept {
		return forward<decltype(self)>(self)._data[N - 1];
	}


	template<size_t N, typename T>
	constexpr auto generic_array<N, T>::data(this auto&& self) noexcept {
		return forward_as_lvalue<decltype(self)>(self)._data;
	}
}

//Iterators
namespace sl {
	template<size_t N, typename T>
	constexpr auto generic_array<N, T>::begin(this auto&& self) noexcept {
		return forward_as_lvalue<decltype(self)>(self)._data;
	}

	
	template<size_t N, typename T>
	constexpr generic_array<N,T>::const_iterator_type generic_array<N, T>::cbegin(this auto const& self) noexcept {
		return self._data;
	}

	
	template<size_t N, typename T>
	constexpr auto generic_array<N, T>::end(this auto&& self) noexcept {
		return forward_as_lvalue<decltype(self)>(self)._data + N;
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



namespace sl {
	template<size_t I, traits::specialization_of<generic_array> ArrayT>
	constexpr auto&& get(ArrayT&& a) noexcept {
		return forward<ArrayT>(a).template get<I>();
	}

	template<size_t N, typename T>
	constexpr void swap(generic_array<N, T>& lhs, generic_array<N, T>& rhs) noexcept(noexcept(lhs.swap(rhs))) {
		return lhs.swap(rhs);
	}
}


namespace sl {
	template<traits::specialization_of<generic_array> R, typename Arg, typename XfrmFn, typename RawArg> 
	requires (traits::is_tuple_like_v<RawArg> || traits::is_container_like_v<RawArg>)
	constexpr remove_cvref_t<R> make(Arg&& array_ish, XfrmFn&& xfrm_each_fn, in_place_adl_tag_type<R>) noexcept {
		constexpr size_t size = algo::min(tuple_traits<R>::size, container_traits<RawArg>::size);
		return impl::make_array_from_container<R>(forward<Arg>(array_ish), forward<XfrmFn>(xfrm_each_fn), index_sequence_of_length<size>);
	}


	template<traits::specialization_of<generic_array> R, typename T, size_t N, typename XfrmFn>
	constexpr remove_cvref_t<R> make(T (&a)[N], XfrmFn&& xfrm_each_fn, in_place_adl_tag_type<R>) noexcept {
		constexpr size_t size = algo::min(tuple_traits<R>::size, N);
		return impl::make_array_from_container<R>(a, forward<XfrmFn>(xfrm_each_fn), index_sequence_of_length<size>);
	}

	template<traits::specialization_of<generic_array> R, typename T, size_t N, typename XfrmFn>
	constexpr remove_cvref_t<R> make(T (&&a)[N], XfrmFn&& xfrm_each_fn, in_place_adl_tag_type<R>) noexcept {
		constexpr size_t size = algo::min(tuple_traits<R>::size, N);
		return impl::make_array_from_container<R>(move(a), forward<XfrmFn>(xfrm_each_fn), index_sequence_of_length<size>);
	}


	template<traits::specialization_of<generic_array> R, typename Arg, size_t N, typename XfrmFn>
	constexpr remove_cvref_t<R> make(Arg&& value, in_place_repeat_tag_type<N>, XfrmFn&& xfrm_each_fn) noexcept {
		constexpr size_t size = algo::min(tuple_traits<R>::size, N);
		return impl::make_array_from_value<R>(forward<Arg>(value), forward<XfrmFn>(xfrm_each_fn), index_sequence_of_length<size>);
	}
}

namespace sl {
	template<template<size_t, typename...> typename R, typename Arg, typename XfrmFn, typename RawArg>
	requires (
		traits::is_tuple_like_v<RawArg> &&
		tuple_traits<RawArg>::homogeneous &&
		traits::same_container_as<R, generic_array, tuple_traits<RawArg>::size, typename tuple_traits<RawArg>::common_type>
	)
	constexpr array<tuple_traits<RawArg>::size, typename tuple_traits<RawArg>::common_type>
	make_deduced(Arg&& array_ish, XfrmFn&& xfrm_each_fn, in_place_container_adl_tag_type<R>) noexcept {
		constexpr size_t size = tuple_traits<RawArg>::size;
		return impl::make_array_from_container<array<size, typename tuple_traits<RawArg>::common_type>>(forward<Arg>(array_ish), forward<XfrmFn>(xfrm_each_fn), index_sequence_of_length<size>);
	}


	template<template<size_t, typename...> typename R, typename T, size_t N, typename XfrmFn>
	requires traits::same_container_as<R, generic_array, N, T>
	constexpr array<N, T> make_deduced(T (&a)[N], XfrmFn&& xfrm_each_fn, in_place_container_adl_tag_type<R>) noexcept {
		constexpr size_t size = N;
		return impl::make_array_from_container<array<N, T>>(a, forward<XfrmFn>(xfrm_each_fn), index_sequence_of_length<size>);
	}

	template<template<size_t, typename...> typename R, typename T, size_t N, typename XfrmFn>
	requires traits::same_container_as<R, generic_array, N, T>
	constexpr array<N, T> make_deduced(T (&&a)[N], XfrmFn&& xfrm_each_fn, in_place_container_adl_tag_type<R>) noexcept {
		constexpr size_t size = N;
		return impl::make_array_from_container<array<N, T>>(move(a), forward<XfrmFn>(xfrm_each_fn), index_sequence_of_length<size>);
	}


	template<template<size_t, typename...> typename R, typename Arg, size_t N, typename XfrmFn>
	requires traits::same_container_as<R, generic_array, N, remove_cvref_t<Arg>>
	constexpr array<N, remove_cvref_t<Arg>> make_deduced(Arg&& value, in_place_repeat_tag_type<N>, XfrmFn&& xfrm_each_fn) noexcept {
		constexpr size_t size = N;
		return impl::make_array_from_value<array<N, remove_cvref_t<Arg>>>(forward<Arg>(value), forward<XfrmFn>(xfrm_each_fn), index_sequence_of_length<size>);
	}
}
