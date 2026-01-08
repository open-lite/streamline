#pragma once
#include "streamline/metaprogramming/in_place.hpp"
#include "streamline/numeric/int.hpp"
#include "streamline/memory/align_value.hpp"


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-attributes"

//allocation
[[nodiscard, gnu::externally_visible, gnu::alloc_size(1), gnu::malloc]] void* operator new  (sl::size_t count, sl::in_place_tag_type const& = sl::in_place_tag) noexcept;
[[nodiscard, gnu::externally_visible, gnu::alloc_size(1), gnu::malloc]] void* operator new[](sl::size_t count, sl::in_place_tag_type const& = sl::in_place_tag) noexcept;

//aligned allocation
[[nodiscard, gnu::externally_visible, gnu::alloc_size(1), gnu::alloc_align(2), gnu::malloc]] void* operator new  (sl::size_t count, sl::align_value align, sl::in_place_tag_type const& = sl::in_place_tag) noexcept;
[[nodiscard, gnu::externally_visible, gnu::alloc_size(1), gnu::alloc_align(2), gnu::malloc]] void* operator new[](sl::size_t count, sl::align_value align, sl::in_place_tag_type const& = sl::in_place_tag) noexcept;


//non-allocating placement
[[nodiscard]] constexpr void* operator new  (sl::size_t, void* p) noexcept {
	return p;
}
[[nodiscard]] constexpr void* operator new[](sl::size_t, void* p) noexcept {
	return p;
}

#pragma GCC diagnostic pop
