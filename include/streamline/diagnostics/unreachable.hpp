#pragma once

namespace sl {
	[[noreturn]] inline void unreachable() {
	    __builtin_unreachable();
	}
}