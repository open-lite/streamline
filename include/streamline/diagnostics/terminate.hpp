#pragma once


#if !defined(_LIBCPP___EXCEPTION_TERMINATE_H) && !defined(__EXCEPTION__) && !defined(_GLIBCXX_CXX_CONFIG_H)

namespace std {
  [[noreturn, gnu::cold]] void terminate() noexcept;
}

namespace std {
	using terminate_handler = void(*)();
	terminate_handler set_terminate(terminate_handler) noexcept;
	terminate_handler get_terminate() noexcept;
}
#else
#include <exception>
#endif


namespace sl {
	using std::terminate;

	using std::terminate_handler;
	using std::set_terminate;
	using std::get_terminate;
}