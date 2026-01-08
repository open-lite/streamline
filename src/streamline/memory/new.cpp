#include "streamline/algorithm/aligned_to.hpp"
#include "streamline/memory/new.hpp"
#include "streamline/memory/new_handler.hpp"

#include <stdlib.h>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-attributes"

//allocation
[[nodiscard, gnu::weak, gnu::externally_visible, gnu::alloc_size(1), gnu::malloc]]
void* operator new  (sl::size_t count, sl::in_place_tag_type const&) noexcept {
	const sl::size_t size = count == 0 ? 1 : count;

	void* p;
	while(!(p = malloc(size))) {
		sl::new_handler_type new_handler = sl::get_new_handler();
		if(new_handler) new_handler();
		else break;
	}
	return p;

}

[[nodiscard, gnu::weak, gnu::externally_visible, gnu::alloc_size(1), gnu::malloc]]
void* operator new[](sl::size_t count, sl::in_place_tag_type const&) noexcept {
	return ::operator new(count, sl::in_place_tag);
}


//aligned allocation
[[nodiscard, gnu::weak, gnu::externally_visible, gnu::alloc_size(1), gnu::alloc_align(2), gnu::malloc]]
void* operator new  (sl::size_t count, sl::align_value align, sl::in_place_tag_type const&) noexcept {
	const sl::size_t size = count == 0 ? 1 : count;
	const sl::size_t alignment = static_cast<sl::size_t>(align) < sizeof(void*) ? sizeof(void*) : static_cast<sl::size_t>(align);
  	const sl::size_t aligned_size = sl::aligned_to(size, alignment);

	void* p;
	while(!(p = aligned_alloc(alignment, aligned_size))) {
		sl::new_handler_type new_handler = sl::get_new_handler();
		if(new_handler) new_handler();
		else break;
	}
	return p;
}

[[nodiscard, gnu::weak, gnu::externally_visible, gnu::alloc_size(1), gnu::alloc_align(2), gnu::malloc]]
void* operator new[](sl::size_t count, sl::align_value align, sl::in_place_tag_type const&) noexcept {
	return ::operator new(count, align, sl::in_place_tag);
}

#pragma GCC diagnostic pop
