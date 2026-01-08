#pragma once
#include "streamline/metaprogramming/in_place.hpp"
#include "streamline/numeric/int.hpp"
#include "streamline/memory/align_value.hpp"


namespace sl {
	struct destroying_delete_tag_type { explicit constexpr destroying_delete_tag_type() = default; };
	inline constexpr destroying_delete_tag_type destroying_delete_tag{};
}


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-attributes"

//deallocation
[[gnu::externally_visible]] void operator delete  (void* ptr, sl::in_place_tag_type const& = sl::in_place_tag) noexcept;
[[gnu::externally_visible]] void operator delete[](void* ptr, sl::in_place_tag_type const& = sl::in_place_tag) noexcept;
[[gnu::externally_visible]] void operator delete  (void* ptr, sl::size_t size, sl::in_place_tag_type const& = sl::in_place_tag) noexcept;
[[gnu::externally_visible]] void operator delete[](void* ptr, sl::size_t size, sl::in_place_tag_type const& = sl::in_place_tag) noexcept;

//aligned deallocation
[[gnu::externally_visible]] void operator delete  (void* ptr, sl::align_value align, sl::in_place_tag_type const& = sl::in_place_tag) noexcept;
[[gnu::externally_visible]] void operator delete[](void* ptr, sl::align_value align, sl::in_place_tag_type const& = sl::in_place_tag) noexcept;
[[gnu::externally_visible]] void operator delete  (void* ptr, sl::size_t size, sl::align_value align, sl::in_place_tag_type const& = sl::in_place_tag) noexcept;
[[gnu::externally_visible]] void operator delete[](void* ptr, sl::size_t size, sl::align_value align, sl::in_place_tag_type const& = sl::in_place_tag) noexcept;

//placement deallocation
[[gnu::externally_visible]] constexpr void operator delete  (void*, void*) noexcept {
	return;
}
[[gnu::externally_visible]] constexpr void operator delete[](void*, void*) noexcept {
	return;
}

#pragma GCC diagnostic pop
