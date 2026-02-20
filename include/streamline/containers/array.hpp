#pragma once
#include "streamline/algorithm/minmax.hpp"
#include "streamline/containers/array.fwd.hpp"
#include "streamline/containers/impl/array_data.hpp"

#include "streamline/functional/functor/identity.hpp"
#include "streamline/metaprogramming/in_place.hpp"
#include "streamline/metaprogramming/integer_sequence.hpp"
#include "streamline/metaprogramming/type_traits/compounded_categories.hpp"
#include "streamline/metaprogramming/type_traits/supported_operations.hpp"
#include "streamline/numeric/int.hpp"
#include "streamline/metaprogramming/tuple_traits.hpp"
#include "streamline/metaprogramming/type_traits/relationships.hpp"


namespace sl {
	template<size_t N, typename T>
	struct generic_array<sl::size_constant_type<N>, T> {
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
		generic_array& fill(V&& val) noexcept;

		template<typename V>
		generic_array& swap(generic_array& other)
		noexcept(N == 0 || sl::traits::is_noexcept_swappable_v<T>); //TODO
	
	//Equality
	public:
		friend constexpr bool operator==(generic_array const& lhs, generic_array const& rhs) noexcept;
		friend constexpr void operator<=>(generic_array const& lhs, generic_array const& rhs) noexcept; //TODO
	};
}



namespace sl {
	template<size_t N, typename T>
	struct container_traits<array<N, T>> {
		constexpr static size_t size = N;
		constexpr static size_t size_bytes = N * sizeof(T);
	};

	template<size_t N, typename T>
	struct tuple_traits<array<N, T>> : container_traits<array<N, T>> {
		constexpr static bool homogeneous = true;
		constexpr static bool unique = N == 0;

		using common_type = T;
		template<size_t>
		using type_of_element = T;
		template<typename>
		using indices_of_type = index_sequence_of_length_type<N>;
	};
}


#include "streamline/containers/array.universal.inl"
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
constexpr auto t = x{{1}, {2}};
constexpr auto w2 = sl::get<0>(t);
constexpr auto w3 = sl::get<0>(const_cast<x&>(t));
constexpr auto w1 = sl::get<0>(x{{1}, {2}});
constexpr auto w4 = sl::get<0>(move(t));
//constexpr bool y = requires { typename x::common_type; };
//using z = typename x::common_type;

namespace sl::test {
	struct immoble{
		int value;

		constexpr immoble() noexcept = default;
		constexpr immoble(int v) noexcept : value(v) {};
		constexpr immoble(immoble const&) noexcept = delete;
		constexpr immoble(immoble&&) noexcept = delete;
		constexpr ~immoble() = default;
	};

	struct move_only{
		int value;

		constexpr move_only() noexcept = default;
		constexpr move_only(int v) noexcept : value(v) {};
		constexpr move_only(move_only const&) noexcept = delete;
		constexpr move_only(move_only&&) noexcept = default;
		constexpr ~move_only() = default;
	};
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedef"
#pragma GCC diagnostic ignored "-Wunused-variable"
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
	//auto mar = sl::forward_as_lvalue<sl::array<3 ,int>&&>(sl::array<3, int>{})._data; //error
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
	constexpr auto immoble_arr = sl::make_deduced<sl::generic_array>(sl::test::move_only(5), sl::in_place_repeat_tag<5>, []<sl::index_t I>(auto&& p, sl::index_constant_type<I>) noexcept {
		return p.value + I;
	});
	constexpr auto sz = immoble_arr.size();
	constexpr auto arr1 = sl::move(immoble_arr[0]);
	constexpr auto arr2 = sl::move(immoble_arr[1]);
	}

	{
	static_assert(sl::traits::is_invocable_each_v<sl::functor::identity&&, sl::tuple<int, int>&&>);
	using R0 = typename sl::invoke_return_type<sl::functor::identity&&, typename sl::tuple_traits<sl::remove_cvref_t<sl::tuple<int, int>&&>>::template type_of_element<0>, sl::index_constant_type<0>>::type;
	using R1 = typename sl::invoke_return_type<sl::functor::identity&&, typename sl::tuple_traits<sl::remove_cvref_t<sl::tuple<int, int>&&>>::template type_of_element<1>, sl::index_constant_type<1>>::type;
	using C = typename sl::common_type<R0, R1>::type;
	using RE = sl::invoke_each_return_type_t<sl::functor::identity&&, sl::tuple<int, int>&&>;
	constexpr auto arr_from_tuple = sl::make_deduced<sl::generic_array>(x{{1}, {2}});
	constexpr auto sz = arr_from_tuple.size();
	constexpr auto arr1 = arr_from_tuple[0];
	constexpr auto arr2 = arr_from_tuple[1];
	}

	{
	constexpr auto arr_from_tuple = sl::make_deduced<sl::generic_array>(x{{1}, {2}}, [](auto&& val, auto seq) noexcept {return static_cast<decltype(val)>(val + static_cast<sl::index_t>(seq)); });
	static_assert(arr_from_tuple.size() == 2);
	static_assert(arr_from_tuple[0] == 1);
	static_assert(arr_from_tuple[1] == 3);
	}

	{
	constexpr static sl::tuple<int, int, int, int> t{{1}, {2}, {3}, {4}};
	using filter = sl::filtered_sequence_t<sl::index_sequence_of_length_type<4>, []<sl::index_t I>(sl::index_constant_type<I>){ return t[sl::index_constant<I>] % 2 == 0; }>;
	constexpr auto filtered_arr_from_tuple = sl::make_deduced<sl::generic_array>(t, sl::functor::identity{}, filter{});
	static_assert(filtered_arr_from_tuple.size() == 2);
	static_assert(filtered_arr_from_tuple[0] == 2);
	static_assert(filtered_arr_from_tuple[1] == 4);
	}

	return 0;
}
#pragma GCC diagnostic pop