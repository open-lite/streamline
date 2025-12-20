#pragma once
#include "streamline/containers/array.fwd.hpp"
#include "streamline/containers/impl/array_data.hpp"

#include "streamline/functional/identity_function.hpp"
#include "streamline/metaprogramming/integer_sequence.hpp"
#include "streamline/metaprogramming/type_traits/compounded_categories.hpp"
#include "streamline/numeric/int.hpp"
#include "streamline/metaprogramming/tuple_traits.hpp"
#include "streamline/metaprogramming/type_traits/relationships.hpp"


namespace sl {
	template<size_t N, typename T>
	struct generic_array<N, T> {
		using value_type      = T;
		using size_type       = sl::size_t;
		using index_type      = sl::index_t;
		using difference_type = sl::ptrdiff_t;

		using pointer_type                = T*;
		using const_pointer_type          = T const*;
		using lvalue_reference_type       = value_type&;
		using const_lvalue_reference_type = value_type const&;
		using rvalue_reference_type       = value_type&&;
		using const_rvalue_reference_type = value_type const&&;
		using iterator_type               = value_type*;
		using const_iterator_type         = value_type const*;
		using reverse_iterator_type       = void; //TODO
		using const_reverse_iterator_type = void; //TODO
	public:
		using pointer                = pointer_type;
		using const_pointer          = const_pointer_type;
		using reference              = lvalue_reference_type;
		using const_reference        = const_lvalue_reference_type;
		using iterator               = iterator_type;
		using const_iterator         = const_iterator_type;
		using reverse_iterator       = reverse_iterator_type;
		using const_reverse_iterator = const_reverse_iterator_type;
	public:
		constexpr static size_type element_count = N;

	public:
		[[no_unique_address]] typename impl::array_data<N, T>::type _data;
		
	//Element access
	public:
		constexpr auto&&         at(this auto&& self, index_type pos) noexcept;
		constexpr auto       try_at(this auto&& self, index_type pos) noexcept;
		constexpr auto&& operator[](this auto&& self, index_type pos) noexcept;
		
		template<index_t I> constexpr auto&& get(this auto&& self) noexcept;
	

		constexpr auto&& front(this auto&& self) noexcept;
		constexpr auto&&  back(this auto&& self) noexcept;

		constexpr auto data(this auto&& self) noexcept;

	//Iterators
	public:
		constexpr auto begin(this auto&& self) noexcept;
		constexpr const_iterator_type cbegin(this auto const& self) noexcept;

		constexpr auto end(this auto&& self) noexcept;
		constexpr const_iterator_type cend(this auto const& self) noexcept;


		constexpr auto rbegin(this auto&& self) noexcept;
		constexpr const_reverse_iterator_type crbegin(this auto const& self) noexcept;

		constexpr auto rend(this auto&& self) noexcept;
		constexpr const_reverse_iterator_type crend(this auto const& self) noexcept;

	//Capacity
	public:
		consteval static bool is_empty() noexcept;
		consteval static bool empty() noexcept;

		consteval static size_type     size() noexcept;
		consteval static size_type max_size() noexcept;

		consteval static size_type     size_bytes() noexcept;
		consteval static size_type max_size_bytes() noexcept;

	//Operations
	public:
		template<typename V>
		generic_array<N, T>& fill(V&& val) noexcept;

		template<typename V>
		generic_array<N, T>& swap(generic_array<N, T>& other) noexcept(N == 0 /*|| is_nothrow_swappable_v<T>*/); //TODO
	
	//Equality
	public:
		friend constexpr bool operator==(generic_array const& lhs, generic_array const& rhs) noexcept;
		friend constexpr void operator<=>(generic_array const& lhs, generic_array const& rhs) noexcept; //TODO
	};
}



namespace sl {
	template<size_t N, typename T>
	struct container_traits<array<N, T>> : container_traits<T[N]> {};

	template<size_t N, typename T>
	struct tuple_traits<array<N, T>> : tuple_traits<T[N]> {};
}


namespace sl {
	template<size_t I, traits::specialization_of<generic_array> ArrayT>
	constexpr auto&& get(ArrayT&& a) noexcept;


	template<size_t N, typename T>
	constexpr void swap(array<N, T>& lhs, array<N, T>& rhs) noexcept(noexcept(lhs.swap(rhs)));
}


namespace sl {
	template<traits::specialization_of<generic_array> R, typename Arg, typename XfrmFn = identity_functor, typename RawArg = remove_cvref_t<Arg>> 
	requires (traits::is_tuple_like_v<RawArg> || traits::is_container_like_v<RawArg>)
	constexpr remove_cvref_t<R> make(Arg&& array_ish, XfrmFn&& xfrm_each_fn = identity_functor{}, in_place_adl_tag_type<R> = in_place_adl_tag<R>) noexcept;


	template<traits::specialization_of<generic_array> R, typename T, size_t N, typename XfrmFn = identity_functor>
	constexpr remove_cvref_t<R> make(T (&a)[N], XfrmFn&& xfrm_each_fn = identity_functor{}, in_place_adl_tag_type<R> = in_place_adl_tag<R>) noexcept;

	template<traits::specialization_of<generic_array> R, typename T, size_t N, typename XfrmFn = identity_functor>
	constexpr remove_cvref_t<R> make(T (&&a)[N], XfrmFn&& xfrm_each_fn = identity_functor{}, in_place_adl_tag_type<R> = in_place_adl_tag<R>) noexcept;


	template<traits::specialization_of<generic_array> R, typename Arg, size_t N = tuple_traits<R>::size, typename XfrmFn = identity_functor>
	constexpr remove_cvref_t<R> make(Arg&& value, in_place_repeat_tag_type<N>, XfrmFn&& xfrm_each_fn = identity_functor{}) noexcept;
}

namespace sl {
	template<template<size_t, typename...> typename R, typename Arg, typename XfrmFn = identity_functor, typename RawArg = remove_cvref_t<Arg>> 
	requires (
		traits::is_tuple_like_v<RawArg> &&
		tuple_traits<RawArg>::homogeneous &&
		traits::same_container_as<R, generic_array, tuple_traits<RawArg>::size, typename tuple_traits<RawArg>::common_type>
	)
	constexpr array<tuple_traits<RawArg>::size, typename tuple_traits<RawArg>::common_type> 
	make_deduced(Arg&& array_ish, XfrmFn&& xfrm_each_fn = identity_functor{}, in_place_container_adl_tag_type<R> = in_place_container_adl_tag<R>) noexcept;


	template<template<size_t, typename...> typename R, typename T, size_t N, typename XfrmFn = identity_functor>
	requires traits::same_container_as<R, generic_array, N, T>
	constexpr array<N, T> make_deduced(T (&a)[N], XfrmFn&& xfrm_each_fn = identity_functor{}, in_place_container_adl_tag_type<R> = in_place_container_adl_tag<R>) noexcept;

	template<template<size_t, typename...> typename R, typename T, size_t N, typename XfrmFn = identity_functor>
	requires traits::same_container_as<R, generic_array, N, T>
	constexpr array<N, T> make_deduced(T (&&a)[N], XfrmFn&& xfrm_each_fn = identity_functor{}, in_place_container_adl_tag_type<R> = in_place_container_adl_tag<R>) noexcept;
	

	template<template<size_t, typename...> typename R, typename Arg, size_t N, typename XfrmFn = identity_functor>
	requires traits::same_container_as<R, generic_array, N, remove_cvref_t<Arg>>
	constexpr array<N, remove_cvref_t<Arg>> make_deduced(Arg&& value, in_place_repeat_tag_type<N>, XfrmFn&& xfrm_each_fn = identity_functor{}) noexcept;
}

#include "streamline/containers/array.inl"



struct test {
	int a;
	[[no_unique_address]] sl::array<0, int> b;
	[[no_unique_address]] sl::array<1, long> c;

	auto f(sl::array<3, int> a) noexcept {
		return sl::forward_as_lvalue<sl::array<3, int>>(a);
	}

};

template<typename T>
using result_t = T const&;

#include "streamline/metaprogramming/move.hpp"

#include "streamline/containers/tuple.hpp"
struct yuck {};

using x = sl::tuple<int, int>;
using y = sl::tuple_traits<x>;
constexpr bool z = sl::traits::is_tuple_like_v<x>;
constexpr auto t = x{1, 2};
constexpr auto w2 = sl::get<0>(t);
constexpr auto w3 = sl::get<0>(const_cast<x&>(t));
constexpr auto w1 = sl::get<0>(x{{{1}, {2}}});
constexpr auto w4 = sl::get<0>(move(t));
//constexpr bool y = requires { typename x::common_type; };
//using z = typename x::common_type;

constexpr int func() noexcept {
	sl::array<3, int> arr{1, 2, 3};
	constexpr static const sl::array<3, long> carr{{1, 2, 3}};

	using a_t = result_t<int>;
	using b_t = result_t<int const>;
	using c_t = result_t<int&>;
	using d_t = result_t<int const&>;
	using e_t = result_t<int&&>;
	using f_t = result_t<int const&&>;

	auto ar = sl::forward_as_lvalue<sl::array<3 ,int>>(arr)._data;
	auto car = sl::forward_as_lvalue<sl::array<3 ,long> const&&>(carr)._data;
	auto mar = sl::forward_as_lvalue<sl::array<3 ,int>&&>(sl::array<3, int>{})._data;
	auto cmar = sl::forward_as_lvalue<sl::array<3 ,long> const&&>(move(carr))._data;

	auto&& i = arr[0];
	constexpr auto&& j = carr[0];
	auto&& k = move(arr)[0];
	constexpr auto&& l = move(carr)[0];

	auto a = arr.begin();
	constexpr auto b = carr.begin();
	auto c = move(arr).begin();
	constexpr auto d = move(carr).begin();


	//auto w = arr.end();
	//constexpr auto x = carr.end();
	//auto y = move(arr).end();
	//constexpr auto z = move(carr).end();

	{
	constexpr auto arr_from_tuple = sl::make_deduced<sl::array>(x{1, 2});
	constexpr auto sz = arr_from_tuple.size();
	constexpr auto arr1 = arr_from_tuple[0];
	constexpr auto arr2 = arr_from_tuple[1];
	}

	{
	constexpr auto arr_from_tuple = sl::make_deduced<sl::array>(x{1, 2}, [](auto&& val, auto seq){return static_cast<decltype(val)>(val + static_cast<sl::index_t>(seq)); });
	constexpr auto sz = arr_from_tuple.size();
	constexpr auto arr1 = arr_from_tuple[0];
	constexpr auto arr2 = arr_from_tuple[1];
	}

	return 0;
}