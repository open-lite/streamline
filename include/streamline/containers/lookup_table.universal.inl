#pragma once
#include "streamline/containers/lookup_table.hpp"
#include "streamline/containers/impl/make_from_container.hpp"
#include "streamline/containers/impl/make_from_value.hpp"


namespace sl {
	template<auto I, traits::specialization_of<generic_lookup_table> LookupTableT>
	constexpr auto&& get(LookupTableT&& lut) noexcept {
		return forward<LookupTableT>(lut).template get<I>();
	}
}


namespace sl {
	template <size_t N, typename Key, typename Value, typename Hash, typename KeyEqual>
	constexpr void swap(lookup_table<N, Key, Value, Hash, KeyEqual>& lhs, lookup_table<N, Key, Value, Hash, KeyEqual>& rhs) 
	noexcept(noexcept(lhs.swap(rhs))) {
		lhs.swap(rhs);
	}
}


namespace sl {
	template<
		traits::specialization_of<generic_lookup_table> R, 
		typename Arg, 
		typename XfrmEachToKeyFn = functor::subscript<0>,
		typename XfrmEachToValueFn = functor::subscript<1>,
		typename XfrmSeq = index_sequence_of_length_type<algo::min(tuple_traits<R>::size, container_traits<remove_cvref_t<Arg>>::size)>,
		typename RawArg = remove_cvref_t<Arg>
	> 
	requires (
		(XfrmSeq::size() == 0 || (
			traits::is_invocable_each_r_v<typename remove_cvref_t<R>::key_type, XfrmEachToKeyFn, Arg&&> &&
			traits::is_invocable_each_r_v<typename remove_cvref_t<R>::mapped_type, XfrmEachToValueFn, Arg&&>
		)) &&
		(traits::is_tuple_like_v<RawArg> || traits::is_container_like_v<RawArg>)
	)
	constexpr remove_cvref_t<R> make(Arg&& array_ish, XfrmEachToKeyFn&& xfrm_each_to_key_fn = {}, XfrmEachToValueFn&& xfrm_each_to_value_fn = {}, XfrmSeq xfrm_seq = {}, in_place_adl_tag_type<R> = in_place_adl_tag<R>) 
	noexcept(XfrmSeq::size() == 0 || (
		traits::is_noexcept_invocable_each_r_v<typename remove_cvref_t<R>::key_type, XfrmEachToKeyFn, Arg&&> &&
		traits::is_noexcept_invocable_each_r_v<typename remove_cvref_t<R>::mapped_type, XfrmEachToValueFn, Arg&&>
	)) {
		return impl::make_lookup_table_from_container<remove_cvref_t<R>>(forward<Arg>(array_ish), forward<XfrmEachToKeyFn>(xfrm_each_to_key_fn), forward<XfrmEachToValueFn>(xfrm_each_to_value_fn), xfrm_seq);
	}
}

namespace sl {
	template<
		template<SL_GENERIC_CONTAINER_TEMPLATE_ARGS()> typename R,
		typename Arg,
		typename XfrmEachToKeyFn = functor::subscript<0>,
		typename XfrmEachToValueFn = functor::subscript<1>,
		typename XfrmSeq = index_sequence_of_length_type<tuple_traits<remove_cvref_t<Arg>>::size>,
		typename RawArg = remove_cvref_t<Arg>
	> 
	requires (
		XfrmSeq::size() > 0 &&
		traits::is_tuple_like_v<RawArg> &&
		traits::is_invocable_each_v<XfrmEachToKeyFn, Arg&&> &&
		traits::is_invocable_each_v<XfrmEachToValueFn, Arg&&> &&
		traits::same_container_as<R, generic_lookup_table, sl::size_constant_type<tuple_traits<XfrmSeq>::size>, int, placeholder_t>
	)
	constexpr auto make_deduced(Arg&& array_ish, XfrmEachToKeyFn&& xfrm_each_to_key_fn = {}, XfrmEachToValueFn&& xfrm_each_to_value_fn = {}, XfrmSeq xfrm_seq = {}, in_place_container_adl_tag_type<R> = in_place_container_adl_tag<R>)
	noexcept(
		traits::is_noexcept_invocable_each_v<XfrmEachToKeyFn, Arg&&> &&
		traits::is_noexcept_invocable_each_v<XfrmEachToValueFn, Arg&&>
	) {
		return impl::make_lookup_table_from_container<lookup_table<tuple_traits<XfrmSeq>::size, 
			remove_cvref_t<invoke_each_return_type_t<XfrmEachToKeyFn, Arg&&>>,
			remove_cvref_t<invoke_each_return_type_t<XfrmEachToValueFn, Arg&&>>
		>>(forward<Arg>(array_ish), forward<XfrmEachToKeyFn>(xfrm_each_to_key_fn), forward<XfrmEachToValueFn>(xfrm_each_to_value_fn), xfrm_seq);
	}
}
