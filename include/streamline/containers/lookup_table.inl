#pragma once
#include "streamline/containers/lookup_table.hpp"
#include "streamline/containers/impl/make_from_container.hpp"
#include "streamline/containers/impl/make_from_value.hpp"

namespace sl {
	// template <size_t N, typename Key, typename Value, typename Hash, typename KeyEqual>
	// template<typename ContainerT, typename HashT, typename KeyEqualT>
	// constexpr generic_lookup_table<N, Key, Value, Hash, KeyEqual>::generic_lookup_table(ContainerT&& contents, HashT&& hash, KeyEqualT&& equal) noexcept 
	// requires 
	// traits::makeable_from<container_type, ContainerT> && 
	// traits::forwaded_noexcept_constructible_from<hasher, HashT> && 
	// traits::forwaded_noexcept_constructible_from<key_equal, KeyEqualT> : 
		// container_type{sl::universal::make<container_type>(forward<ContainerT>(contents))},
		// _table(sl::universal::make<impl::hash_table<storage_size, container_type>>(*this, forward_as_lvalue<HashT>(hash), forward_as_lvalue<KeyEqualT>(equal))),
		// _hash{forward<HashT>(hash)}, _key_equal(forward<KeyEqualT>(equal)) {
	// }

	// template <size_t N, typename Key, typename Value, typename Hash, typename KeyEqual>
	// template<typename HashT, typename KeyEqualT>
	// constexpr generic_lookup_table<N, Key, Value, Hash, KeyEqual>::generic_lookup_table(initializer_list<value_type> il, HashT&& hash, KeyEqualT&& equal) noexcept 
	// requires
	// traits::forwaded_noexcept_constructible_from<hash_type, HashT> && 
	// traits::forwaded_noexcept_constructible_from<key_equal_type, KeyEqualT> : 
		// container_type{sl::universal::make<container_type>(il)},
		// _table(sl::universal::make<impl::hash_table<storage_size, container_type>>(*this, forward_as_lvalue<HashT>(hash), forward_as_lvalue<KeyEqualT>(equal))),
		// _hash{forward<HashT>(hash)}, _key_equal(forward<KeyEqualT>(equal)) {
	// }
}


namespace sl {
	template <size_t N, typename Key, typename Value, typename Hash, typename KeyEqual>
	template<typename K> 
	constexpr auto&& generic_lookup_table<N, Key, Value, Hash, KeyEqual>::at(this auto&& self, K&& key) noexcept requires compatible_key<K> {
		auto it = self.find(forward<K>(key));
		if (it != self.end()) return forward_like<decltype(self)>(it->second);
		terminate();
	}
	
	template <size_t N, typename Key, typename Value, typename Hash, typename KeyEqual>
	template<typename K> 
	constexpr auto generic_lookup_table<N, Key, Value, Hash, KeyEqual>::try_at(this auto&& self, K&& key) noexcept requires compatible_key<K> {
		//TODO
	}
	
	template <size_t N, typename Key, typename Value, typename Hash, typename KeyEqual>
	template<typename K> 
	constexpr auto&& generic_lookup_table<N, Key, Value, Hash, KeyEqual>::operator[](this auto&& self, K&& key) noexcept requires compatible_key<K> {
		auto it = self.find(forward<K>(key));
		return forward_like<decltype(self)>(it->operator[](second_constant));
	}



	template<size_t N, typename Key, typename Value, typename Hash, typename KeyEqual>
	template<auto I>
	constexpr auto&& generic_lookup_table<N, Key, Value, Hash, KeyEqual>::get(this auto&& self) noexcept requires compatible_key<decltype(I)> {
		return forward_like<decltype(self)>(self.operator[](I));
	}
}

namespace sl {
	template <size_t N, typename Key, typename Value, typename Hash, typename KeyEqual>
	template<typename K> 
	constexpr size_t generic_lookup_table<N, Key, Value, Hash, KeyEqual>::count(K&& key) const noexcept requires compatible_key<K> {
		return static_cast<size_t>(this->find(forward<K>(key)) != this->end());
	}

	
	template <size_t N, typename Key, typename Value, typename Hash, typename KeyEqual>
	template<typename K> 
	constexpr auto generic_lookup_table<N, Key, Value, Hash, KeyEqual>::find(this auto&& self, K&& key) noexcept requires compatible_key<K> {
		const index_t pos = self.lookup(key);
		auto it = forward_as_lvalue<decltype(self)>(self).begin() + pos;

		if (it != forward_as_lvalue<decltype(self)>(self).end() && self._key_equal(it->operator[](first_constant), forward<K>(key))) return it;
		return forward_as_lvalue<decltype(self)>(self).end();
	}


	template <size_t N, typename Key, typename Value, typename Hash, typename KeyEqual>
	template<typename K> 
	constexpr bool generic_lookup_table<N, Key, Value, Hash, KeyEqual>::contains(K&& key) const noexcept requires compatible_key<K> {
		return this->find(forward<K>(key)) != this->end();
	}
}

namespace sl {
	template <size_t N, typename Key, typename Value, typename Hash, typename KeyEqual>
	template<typename K> 
	constexpr auto generic_lookup_table<N, Key, Value, Hash, KeyEqual>::equal_range(this auto&& self, K&& key) noexcept requires compatible_key<K> {
		const auto it = forward_as_lvalue<decltype(self)>(self).find(key);
		if (it != forward_as_lvalue<decltype(self)>(self).end()) return make_pair(it, it + 1);
		return make_pair(forward_as_lvalue<decltype(self)>(self).end(), forward_as_lvalue<decltype(self)>(self).end());
	}
}


namespace sl {
	template <size_t N, typename Key, typename Value, typename Hash, typename KeyEqual>
	consteval size_t
	generic_lookup_table<N, Key, Value, Hash, KeyEqual>::bucket_count() noexcept {
		return hash_table_type::storage_size;
	}
	
	template <size_t N, typename Key, typename Value, typename Hash, typename KeyEqual>
	consteval size_t
	generic_lookup_table<N, Key, Value, Hash, KeyEqual>::max_bucket_count() noexcept {
		return hash_table_type::storage_size;
	}
}


namespace sl {
	template <size_t N, typename Key, typename Value, typename Hash, typename KeyEqual>
	constexpr auto generic_lookup_table<N, Key, Value, Hash, KeyEqual>::hash_function(this auto&& self) noexcept {
		return forward_as_lvalue<decltype(self)>(self)._hash;
	}
	
	template <size_t N, typename Key, typename Value, typename Hash, typename KeyEqual>
	constexpr auto generic_lookup_table<N, Key, Value, Hash, KeyEqual>::key_eq(this auto&& self) noexcept {
		return forward_as_lvalue<decltype(self)>(self)._key_equal;
	}
}


namespace sl {
	template <size_t N, typename Key, typename Value, typename Hash, typename KeyEqual>
	template <typename K>
	constexpr index_t generic_lookup_table<N, Key, Value, Hash, KeyEqual>::lookup(K const& key) const noexcept {
		auto const d = _table._seed_table[_hash(key, _table._seed) % hash_table_type::storage_size];

		if (!d.is_seed())
			return static_cast<index_t>(d.value);
		return _table._idx_table[_hash(key, static_cast<index_t>(d.value)) % hash_table_type::storage_size];
	}
}