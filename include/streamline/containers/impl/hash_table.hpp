#pragma once
#include <frozen/bits/algorithms.h>
#include <frozen/random.h>
#include <frozen/bits/pmh.h>

#include "streamline/containers/impl/seed_or_index.hpp"
#include "streamline/numeric/int.hpp"
#include "streamline/containers/array.hpp"


namespace sl::impl {
	template<typename ContainerT, typename HashT, typename KeyEqualT>
	struct hash_table {
		using container_type = ContainerT;
		constexpr static size_t storage_size = (frozen::bits::next_highest_power_of_two(container_type::size()) * (container_type::size() < 32 ? 2 : 1));
	public:
		index_t _seed;
        array<storage_size, impl::seed_or_index> _seed_table;
        array<storage_size, index_t> _idx_table;

	public:
		constexpr hash_table(ContainerT const& contents, HashT const& hash, KeyEqualT const& key_equal) noexcept : 
			_seed{},
			_seed_table{sl::universal::make<array<storage_size, impl::seed_or_index>>(impl::seed_or_index{false, container_type::size()}, in_place_repeat_tag<container_type::size()>)},
			_idx_table{sl::universal::make<array<storage_size, index_t>>(container_type::size(), in_place_repeat_tag<container_type::size()>)}
		{
			constexpr static size_t bucket_size = frozen::bits::pmh_buckets<storage_size>::bucket_max;
			using prg_type = frozen::default_prg_t;
			using bucket_type = frozen::bits::cvector<index_t, bucket_size>;
			using bucket_ref_type = typename frozen::bits::pmh_buckets<storage_size>::bucket_ref;

			array<storage_size, bucket_type> buckets{};
			array<storage_size, bucket_ref_type> bucket_refs = 
				sl::universal::make<decltype(bucket_refs)>(buckets, []<index_t I>(auto const& bucket, index_constant_type<I>) -> bucket_ref_type{
					return bucket_ref_type{I, &bucket};
				});
			prg_type prg{};
			//array<storage_size, size_t> bucket_sizes;



			while (true) {
				_seed = prg();
				bool rejected = false;
				for (index_t i = 0; i < container_type::size(); ++i) {
					auto& bucket = buckets[hash(contents[i].first, _seed) % storage_size];
					if (bucket.size() >= bucket_size) {
						rejected = true;
						break;
					}
					bucket.push_back(i);
				}
				if (!rejected) break;
				buckets = decltype(buckets){};
			}

			#ifndef NDEBUG
			for(bucket_type const& bucket : buckets)
				for(std::size_t i = 1; i < bucket.size(); ++i)
					constexpr_assert(!key_equal(contents[0].first, contents[i].first), "unique keys");
			#endif

			frozen::bits::quicksort(bucket_refs.begin(), bucket_refs.end() - 1, frozen::bits::bucket_size_compare{});

			// Step 3: Map the items in buckets into hash tables.
			for (bucket_ref_type const& bucket_ref : bucket_refs) {
				const size_t bsize = bucket_ref.size();

				switch(bsize) {
				case 1:
					_seed_table[bucket_ref.hash] = {false, static_cast<index_t>(bucket_ref[0])};
					break;
				default:
					impl::seed_or_index d{true, prg()};
					frozen::bits::cvector<index_t, bucket_size> bucket_slots;

					while (bucket_slots.size() < bsize) {
						auto slot = hash(contents[bucket_ref[bucket_slots.size()]].first, static_cast<index_t>(d.value)) % storage_size;

						if (_idx_table[slot] != container_type::size() || !frozen::bits::all_different_from(bucket_slots, slot)) {
							bucket_slots.clear();
							d = {true, prg()};
							continue;
						}

						bucket_slots.push_back(slot);
					}

					// Put successful seed in G, and put indices to items in their slots
					// assert(bucket.hash == hash(key(items[bucket[0]]), step_one.seed) % M);
					_seed_table[bucket_ref.hash] = d;
					for (std::size_t i = 0; i < bsize; ++i)
						_idx_table[bucket_slots[i]] = bucket_ref[i];
					break;
				}
			}
		}
	};
}