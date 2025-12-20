#pragma once
#include "streamline/numeric/int.hpp"
#include "streamline/numeric/numeric_traits.hpp"

namespace sl::impl {

    struct seed_or_index {
        using value_type = index_t;
    public:
        value_type value = 0;

    private:
        constexpr static value_type highest_bit = ~(sl::numeric_traits<value_type>::max >> 1);

    public:
      constexpr bool is_seed() const { return value & highest_bit; }

      constexpr seed_or_index() = default;
      constexpr seed_or_index(bool seed, value_type val)
        : value(seed ? (val | highest_bit) : (val & ~highest_bit)) {}

    };
}