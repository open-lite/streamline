#pragma once
#include "streamline/containers/array.hpp"
#include "streamline/diagnostics/terminate.hpp"
#include "streamline/algorithm/minmax.hpp"

#include "streamline/containers/impl/make_from_container.hpp"
#include "streamline/containers/impl/make_from_value.hpp"


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
	template<traits::specialization_of<generic_array> R, typename Arg, typename XfrmEachFn, typename XfrmSeq, typename RawArg>
	requires (
		traits::is_noexcept_invocable_each_r_v<typename remove_cvref_t<R>::value_type, XfrmEachFn, RawArg> &&
		(traits::is_tuple_like_v<RawArg> || traits::is_container_like_v<RawArg>)
	)
	constexpr remove_cvref_t<R> make(Arg&& array_ish, XfrmEachFn&& xfrm_each_fn, XfrmSeq xfrm_seq, in_place_adl_tag_type<R>) noexcept {
		return impl::make_array_from_container<R>(forward<Arg>(array_ish), forward<XfrmEachFn>(xfrm_each_fn), xfrm_seq);
	}


	template<traits::specialization_of<generic_array> R, typename Arg, size_t N, typename XfrmEachFn, typename XfrmSeq>
	requires traits::is_noexcept_invocable_r_v<typename remove_cvref_t<R>::value_type, XfrmEachFn, Arg, index_constant_type<0>>
	constexpr remove_cvref_t<R> make(Arg&& value, in_place_repeat_tag_type<N>, XfrmEachFn&& xfrm_each_fn, XfrmSeq xfrm_seq) noexcept {
		return impl::make_array_from_value<R>(forward<Arg>(value), forward<XfrmEachFn>(xfrm_each_fn), xfrm_seq);
	}
}

namespace sl {
	template<template<size_t, typename...> typename R, typename Arg, typename XfrmEachFn, typename XfrmSeq, typename RawArg>
	requires (
		traits::is_tuple_like_v<RawArg> &&
		traits::is_noexcept_invocable_each_v<XfrmEachFn, RawArg> &&
		traits::same_container_as<R, generic_array, tuple_traits<XfrmSeq>::size, placeholder_t>
	)
	constexpr auto make_deduced(Arg&& array_ish, XfrmEachFn&& xfrm_each_fn, XfrmSeq xfrm_seq, in_place_container_adl_tag_type<R>) noexcept {
		return impl::make_array_from_container<array<XfrmSeq::size(), remove_cvref_t<invoke_each_result_t<XfrmEachFn, RawArg>>>>(
			forward<Arg>(array_ish), forward<XfrmEachFn>(xfrm_each_fn), xfrm_seq
		);
	}


	template<template<size_t, typename...> typename R, typename Arg, size_t N, typename XfrmEachFn, typename XfrmSeq>
	requires (
		traits::is_noexcept_invocable_v<XfrmEachFn, Arg, index_constant_type<0>> &&
		traits::same_container_as<R, generic_array, N, placeholder_t>
	)
	constexpr auto make_deduced(Arg&& value, in_place_repeat_tag_type<N>, XfrmEachFn&& xfrm_each_fn, XfrmSeq xfrm_seq) noexcept {
		return impl::make_array_from_value<array<XfrmSeq::size(), remove_cvref_t<invoke_result_t<XfrmEachFn, Arg, index_constant_type<0>>>>>(
			forward<Arg>(value), forward<XfrmEachFn>(xfrm_each_fn), xfrm_seq
		);
	}
}
