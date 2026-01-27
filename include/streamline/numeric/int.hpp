#pragma once
#include <stddef.h>
#include <stdint.h>


namespace sl {
	using ::size_t;
	using index_t = ::size_t;
	using ::ptrdiff_t;
	using offset_t = ::ptrdiff_t;
	using uoffset_t = ::size_t;
	using ::max_align_t;
	using nullptr_t = decltype(nullptr);
}

namespace sl {
	using ::int8_t;
	using ::int16_t;
	using ::int32_t;
	using ::int64_t;

	using ::uint8_t;
	using ::uint16_t;
	using ::uint32_t;
	using ::uint64_t;


	using ::int_fast8_t;
	using ::int_fast16_t;
	using ::int_fast32_t;
	using ::int_fast64_t;

	using ::uint_fast8_t;
	using ::uint_fast16_t;
	using ::uint_fast32_t;
	using ::uint_fast64_t;


	using ::int_least8_t;
	using ::int_least16_t;
	using ::int_least32_t;
	using ::int_least64_t;

	using ::uint_least8_t;
	using ::uint_least16_t;
	using ::uint_least32_t;
	using ::uint_least64_t;
}


namespace sl {
	enum class byte : unsigned char {};

	using ::intmax_t;
	using ::uintmax_t;

	using ::intptr_t;
	using ::uintptr_t;
}


namespace sl {
	constexpr size_t dynamic_extent = static_cast<size_t>(-1);
	constexpr index_t npos = static_cast<index_t>(-1);
}