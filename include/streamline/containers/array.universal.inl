#pragma once
#include "streamline/containers/array.hpp"

#include "streamline/containers/impl/make_from_container.hpp"
#include "streamline/containers/impl/make_from_value.hpp"


namespace sl {
	template<size_t I, traits::specialization_of<generic_array> ArrayT>
	constexpr auto&& get(ArrayT&& a) noexcept {
		return sl::forward<ArrayT>(a).template get<I>();
	}

	template<size_t N, typename T>
	constexpr void swap(array<N, T>& lhs, array<N, T>& rhs) noexcept(noexcept(lhs.swap(rhs))) {
		return lhs.swap(rhs);
	}
}



namespace sl {
	template<
		traits::specialization_of<generic_array> R,
		typename Arg,
		typename XfrmEachFn = functor::identity,
		typename XfrmSeq = index_sequence_of_length_type<algo::min(tuple_traits<R>::size, container_traits<remove_cvref_t<Arg>>::size)>,
		typename RawArg = remove_cvref_t<Arg>
	> 
	requires (
		(XfrmSeq::size() == 0 || traits::is_invocable_each_r_v<typename remove_cvref_t<R>::value_type, XfrmEachFn&&, Arg&&>) &&
		(traits::is_tuple_like_v<RawArg> || traits::is_container_like_v<RawArg>)
	)
	constexpr remove_cvref_t<R> make(Arg&& array_ish, XfrmEachFn&& xfrm_each_fn = {}, XfrmSeq xfrm_seq = {}, in_place_adl_tag_type<R> = in_place_adl_tag<R>)
	noexcept(XfrmSeq::size() == 0 || traits::is_noexcept_invocable_each_r_v<typename remove_cvref_t<R>::value_type, XfrmEachFn&&, Arg&&>) {
		return impl::make_array_from_container<R>(sl::forward<Arg>(array_ish), sl::forward<XfrmEachFn>(xfrm_each_fn), xfrm_seq);
	}


	template<
		traits::specialization_of<generic_array> R, 
		typename Arg, 
		size_t N = tuple_traits<R>::size, 
		typename XfrmEachFn = functor::identity,
		typename XfrmSeq = index_sequence_of_length_type<algo::min(tuple_traits<R>::size, N)>
	>
	requires traits::is_invocable_r_v<typename remove_cvref_t<R>::value_type, XfrmEachFn&&, Arg&&, index_constant_type<0>>
	constexpr remove_cvref_t<R> make(Arg&& value, in_place_repeat_tag_type<N>, XfrmEachFn&& xfrm_each_fn = {}, XfrmSeq xfrm_seq = {})
	noexcept(traits::is_noexcept_invocable_r_v<typename remove_cvref_t<R>::value_type, XfrmEachFn&&, Arg&&, index_constant_type<0>>) {
		return impl::make_array_from_value<R>(sl::forward<Arg>(value), sl::forward<XfrmEachFn>(xfrm_each_fn), xfrm_seq);
	}
}

namespace sl {
	template<
		template<SL_GENERIC_CONTAINER_TEMPLATE_ARGS()> typename R,
		typename Arg,
		typename XfrmEachFn = functor::identity,
		typename XfrmSeq = index_sequence_of_length_type<tuple_traits<remove_cvref_t<Arg>>::size>,
		typename RawArg = remove_cvref_t<Arg>
	>
	requires (
		XfrmSeq::size() > 0 &&
		traits::is_tuple_like_v<RawArg> &&
		traits::is_invocable_each_v<XfrmEachFn&&, Arg&&> &&
		traits::same_container_as<R, generic_array, sl::size_constant_type<tuple_traits<XfrmSeq>::size>, placeholder_t>
	)
	constexpr auto make_deduced(Arg&& array_ish, XfrmEachFn&& xfrm_each_fn = {}, XfrmSeq xfrm_seq = {}, in_place_container_adl_tag_type<R> = in_place_container_adl_tag<R>)
	noexcept(traits::is_noexcept_invocable_each_v<XfrmEachFn&&, Arg&&>) {
		return impl::make_array_from_container<array<XfrmSeq::size(), remove_cvref_t<invoke_each_return_type_t<XfrmEachFn&&, Arg&&>>>>(
			sl::forward<Arg>(array_ish), sl::forward<XfrmEachFn>(xfrm_each_fn), xfrm_seq
		);
	}
	

	template<
		template<SL_GENERIC_CONTAINER_TEMPLATE_ARGS()> typename R, 
		typename Arg, 
		size_t N, 
		typename XfrmEachFn = functor::identity,
		typename XfrmSeq = index_sequence_of_length_type<N>
	>
	requires (
		traits::is_invocable_v<XfrmEachFn&&, Arg&&, index_constant_type<0>> &&
		traits::same_container_as<R, generic_array, sl::size_constant_type<N>, placeholder_t>
	)
	constexpr auto make_deduced(Arg&& value, in_place_repeat_tag_type<N>, XfrmEachFn&& xfrm_each_fn = {}, XfrmSeq xfrm_seq = {})
	noexcept(traits::is_noexcept_invocable_v<XfrmEachFn&&, Arg&&, index_constant_type<0>>) {
		return impl::make_array_from_value<array<XfrmSeq::size(), remove_cvref_t<invoke_return_type_t<XfrmEachFn&&, Arg&&, index_constant_type<0>>>>>(
			sl::forward<Arg>(value), sl::forward<XfrmEachFn>(xfrm_each_fn), xfrm_seq
		);
	}
}
