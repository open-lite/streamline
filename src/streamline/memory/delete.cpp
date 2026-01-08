#include "streamline/memory/delete.hpp"

#include <stdlib.h>

#include "streamline/metaprogramming/in_place.hpp"
#include "streamline/numeric/int.hpp"
#include "streamline/memory/align_value.hpp"


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-attributes"

//deallocation
[[gnu::weak, gnu::externally_visible]]
void operator delete  (void* ptr, sl::in_place_tag_type const&) noexcept {
	return free(ptr);
}

[[gnu::weak, gnu::externally_visible]]
void operator delete[](void* ptr, sl::in_place_tag_type const&) noexcept {
	return ::operator delete(ptr, sl::in_place_tag);
}

[[gnu::weak, gnu::externally_visible]]
void operator delete  (void* ptr, sl::size_t, sl::in_place_tag_type const&) noexcept {
	return ::operator delete(ptr, sl::in_place_tag);
}

[[gnu::weak, gnu::externally_visible]]
void operator delete[](void* ptr, sl::size_t, sl::in_place_tag_type const&) noexcept {
	return ::operator delete(ptr, sl::in_place_tag);
}


//aligned deallocation
[[gnu::weak, gnu::externally_visible]]
void operator delete  (void* ptr, sl::align_value, sl::in_place_tag_type const&) noexcept {
	return free(ptr);
}

[[gnu::weak, gnu::externally_visible]]
void operator delete[](void* ptr, sl::align_value align, sl::in_place_tag_type const&) noexcept {
	return ::operator delete(ptr, align, sl::in_place_tag);
}

[[gnu::weak, gnu::externally_visible]]
void operator delete  (void* ptr, sl::size_t, sl::align_value align, sl::in_place_tag_type const&) noexcept {
	return ::operator delete(ptr, align, sl::in_place_tag);
}

[[gnu::weak, gnu::externally_visible]]
void operator delete[](void* ptr, sl::size_t, sl::align_value align, sl::in_place_tag_type const&) noexcept {
	return ::operator delete(ptr, align, sl::in_place_tag);
}

#pragma GCC diagnostic pop
