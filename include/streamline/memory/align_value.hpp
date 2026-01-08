#pragma once

#if !defined(_LIBCPP___NEW_ALIGN_VAL_T_H) && !defined(_NEW)
#define _LIBCPP___NEW_ALIGN_VAL_T_H
#define _NEW
#include "streamline/numeric/int.hpp"

namespace std {
	enum class align_val_t : sl::size_t {};
}

#else 
#include <new>
#endif


namespace sl {
	using align_value = std::align_val_t;
}