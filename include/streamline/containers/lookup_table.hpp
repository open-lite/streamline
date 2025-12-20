#pragma once
#include "streamline/containers/lookup_table.fwd.hpp"

#include <frozen/bits/algorithms.h>
#include <frozen/random.h>
#include <frozen/bits/pmh.h>

#include "streamline/algorithm/lookup_table_hash.hpp"
#include "streamline/containers/array.hpp"
#include "streamline/containers/impl/seed_or_index.hpp"
#include "streamline/containers/impl/hash_table.hpp"
#include "streamline/containers/pair.hpp"
#include "streamline/functional/comparison.hpp"
#include "streamline/metaprogramming/type_traits/relationships.hpp"
#include "streamline/metaprogramming/type_traits/supported_operations.hpp"
#include "streamline/numeric/int.hpp"


namespace sl {
	template <size_t N, typename Key, typename Value, typename Hash, typename KeyEqual>
	struct generic_lookup_table<N, Key, Value, Hash, KeyEqual> : public array<N, pair<const Key, Value>> {
	private:
		template<typename K>
		constexpr static bool compatible_key = requires (Hash const& hash, KeyEqual const& key_equal, Key const& key1, K&& key2, index_t const& seed) { 
			{ hash(forward<K>(key2), seed) } noexcept;
			{ key_equal(key1, forward<K>(key2)) } noexcept;
		};

	public:
		using key_type        = Key;
		using mapped_type     = Value;
		using value_type      = pair<const Key, Value>;
		using container_type  = array<N, value_type>;
		using size_type       = typename container_type::size_type;
		using difference_type = typename container_type::difference_type;
		using hash_type       = Hash;
		using key_equal_type  = KeyEqual;
		using hash_table_type = impl::hash_table<container_type, hash_type, key_equal_type>;

		using pointer_type                = typename container_type::pointer_type;
		using const_pointer_type          = typename container_type::const_pointer_type;
		using lvalue_reference_type       = typename container_type::lvalue_reference_type;
		using const_lvalue_reference_type = typename container_type::const_lvalue_reference_type;
		using rvalue_reference_type       = typename container_type::rvalue_reference_type;
		using const_rvalue_reference_type = typename container_type::const_rvalue_reference_type;
		using iterator_type               = typename container_type::iterator_type;
		using const_iterator_type         = typename container_type::const_iterator_type;
		using reverse_iterator_type       = typename container_type::reverse_iterator_type;
		using const_reverse_iterator_type = typename container_type::const_reverse_iterator_type;
	public:
		using hasher = hash_type;
		using key_equal = key_equal_type;

		using pointer                = pointer_type;
		using const_pointer          = const_pointer_type;
		using reference              = lvalue_reference_type;
		using const_reference        = const_lvalue_reference_type;
		using iterator               = iterator_type;
		using const_iterator         = const_iterator_type;
		using reverse_iterator       = reverse_iterator_type;
		using const_reverse_iterator = const_reverse_iterator_type;

	public:
        [[no_unique_address]] hash_type _hash{};
		[[no_unique_address]] key_equal_type _key_equal{};
		//this is SUS but not UB
        hash_table_type _table{*this, _hash, _key_equal};


	public:
		//constexpr generic_lookup_table() noexcept = default;

	public:
		// template<typename ContainerT, typename HashT = hash_type, typename KeyEqualT = key_equal_type>
		// constexpr generic_lookup_table(ContainerT&& contents, HashT&& hash = HashT{}, KeyEqualT&& equal = KeyEqualT{}) noexcept requires 
		// traits::makeable_from<container_type, ContainerT> && 
		// traits::forwaded_noexcept_constructible_from<hash_type, HashT> && 
		// traits::forwaded_noexcept_constructible_from<key_equal_type, KeyEqualT>;

		// template<typename HashT = hash_type, typename KeyEqualT = key_equal_type>
		// constexpr generic_lookup_table(initializer_list<value_type> il, HashT&& hash = HashT{}, KeyEqualT&& equal = KeyEqualT{}) noexcept requires 
		// traits::forwaded_noexcept_constructible_from<hash_type, HashT> && 
		// traits::forwaded_noexcept_constructible_from<key_equal_type, KeyEqualT>;

	private:
		constexpr void make_hash_tables() noexcept;

	public:
		template<typename K> constexpr auto&& at(this auto&& self, K&& key) noexcept requires compatible_key<K>;
		template<typename K> constexpr auto try_at(this auto&& self, K&& key) noexcept requires compatible_key<K>;
		template<typename K> constexpr auto&& operator[](this auto&& self, K&& key) noexcept requires compatible_key<K>;

		template<typename K> constexpr size_t count(K&& key) const noexcept requires compatible_key<K>;
		template<typename K> constexpr auto find(this auto&& self, K&& key) noexcept requires compatible_key<K>;
		template<typename K> constexpr bool contains(K&& key) const noexcept requires compatible_key<K>;

		template<typename K> constexpr auto equal_range(this auto&& self, K&& key) noexcept requires compatible_key<K>;

	public:
		consteval static size_t bucket_count() noexcept;
		consteval static size_t max_bucket_count() noexcept;

	public:
		constexpr auto hash_function(this auto&& self) noexcept; 
		constexpr auto key_eq(this auto&& self) noexcept;
	
	private:
        template <typename K> constexpr index_t lookup(K const& key) const noexcept;
        constexpr value_type const& find_by_index(index_t i) const& noexcept;
	};
}


namespace sl {
	template<
		template<size_t, typename...> typename TupleLikeT, 
		size_t N, typename... Args, typename Key, typename Value, 
		typename Hash = algo::lookup_table_hash<Key>, typename KeyEqual = equal_functor
	>
	requires traits::tuple_like<TupleLikeT<N, pair<Key, Value>, Args...>>
	generic_lookup_table(TupleLikeT<N, pair<Key, Value>, Args...>, Hash, KeyEqual) -> generic_lookup_table<N, Key, Value, Hash, KeyEqual>;

	template<
		template<size_t, typename...> typename TupleLikeT, 
		size_t N, typename... Args, typename Key, typename Value, 
		typename Hash = algo::lookup_table_hash<Key>, typename KeyEqual = equal_functor
	>
	requires traits::tuple_like<TupleLikeT<N, pair<const Key, Value>, Args...>>
	generic_lookup_table(TupleLikeT<N, pair<const Key, Value>, Args...>, Hash, KeyEqual) -> generic_lookup_table<N, Key, Value, Hash, KeyEqual>;
}

namespace sl {
	template <size_t N, typename Key, typename Value, typename Hash, typename KeyEqual>
	struct container_traits<lookup_table<N, Key, Value, Hash, KeyEqual>> : 
		container_traits<typename lookup_table<N, Key, Value, Hash, KeyEqual>::container_type> {};

	template <size_t N, typename Key, typename Value, typename Hash, typename KeyEqual>
	struct tuple_traits<lookup_table<N, Key, Value, Hash, KeyEqual>> : 
		tuple_traits<typename lookup_table<N, Key, Value, Hash, KeyEqual>::container_type> {};
}


#include "streamline/containers/lookup_table.inl"




//Placeholder for test suites
namespace sl::test {
	constexpr auto arr123 = array<3, const frozen::bits::cvector<unsigned long, 4>>{{
		{4, 1}, {4, 2}, {4, 3}
	}};
	//constexpr auto arr_from_value = sl::universal::make<array<3, typename frozen::bits::pmh_buckets<4>::bucket_ref>>(arr123, []<index_t I>(auto const& bucket, index_constant_type<I>) {
	//	return typename frozen::bits::pmh_buckets<4>::bucket_ref{I, &bucket};
	//});
	//constexpr auto sz = arr_from_value.size();
	//constexpr auto arr1 = arr_from_value[0];
	//constexpr auto arr2 = arr_from_value[1];


	using oof = lookup_table<4, sl::uint64_t, array<2, empty_t>>;
	constexpr typename oof::container_type yikes{{
			{0, array<2, empty_t>{}},
			{1, array<2, empty_t>{}},
			{2, array<2, empty_t>{}},
			{3, array<2, empty_t>{}}
	}};
	
	//constexpr impl::hash_table<oof::bucket_count(), typename oof::container_type> dab = sl::impl::make<impl::hash_table<oof::bucket_count(), typename oof::container_type>>(
	//	yikes, typename oof::hash_type{}, typename oof::key_equal_type{}
	//); 
	
	
	constexpr lookup_table<4, int, array<2, int>> yeet{{{
		{0, array<2, int>{1, 2}},
		{1124135, array<2, int>{3, 4}},
		{212351, array<2, int>{5, 6}},
		{1259139578, array<2, int>{7, 8}}
	}}};
	static_assert(yeet[0][0] == 1 && yeet[0][1] == 2);
	static_assert(yeet[1124135][0] == 3 && yeet[1124135][1] == 4);
	static_assert(yeet[212351][0] == 5 && yeet[212351][1] == 6);
	static_assert(yeet[1259139578][0] == 7 && yeet[1259139578][1] == 8);


	
	struct immoble{
		int value;

		constexpr immoble() noexcept = default;
		constexpr immoble(int v) noexcept : value(v) {};
		constexpr immoble(immoble const&) noexcept = delete;
		constexpr immoble(immoble&&) noexcept = delete;
	};
	constexpr lookup_table<4, sl::uint64_t, immoble> doh{{{
		{0, immoble{1}},
		{1124135, immoble{3}},
		{212351, immoble{5}},
		{1259139578135, immoble{7}}
	}}};
	static_assert(doh[static_cast<uint64_t>(0)].value == 1);
	static_assert(doh[static_cast<uint64_t>(1124135)].value == 3);
	static_assert(doh[static_cast<uint64_t>(212351)].value == 5);
	static_assert(doh[static_cast<uint64_t>(1259139578135)].value == 7);


	constexpr array<4, pair<const sl::uint64_t, array<2, empty_t>>> arrr = sl::universal::make_deduced<array>(
		array<4, pair<const sl::uint64_t, array<2, empty_t>>>{{
			{0, array<2, empty_t>{}},
			{1, array<2, empty_t>{}},
			{2, array<2, empty_t>{}},
			{3, array<2, empty_t>{}}
		}}
	);
	constexpr array<4, pair<const sl::uint64_t, array<2, empty_t>>> arrm = sl::universal::make<array<4, pair<const sl::uint64_t, array<2, empty_t>>>>(
		array<4, pair<const sl::uint64_t, array<2, empty_t>>>{{
			{0, array<2, empty_t>{}},
			{1, array<2, empty_t>{}},
			{2, array<2, empty_t>{}},
			{3, array<2, empty_t>{}}
		}}
	);
}