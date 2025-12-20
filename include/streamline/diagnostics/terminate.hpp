#pragma once


#if !defined(_LIBCPP___EXCEPTION_TERMINATE_H) && !defined(__EXCEPTION__)
#define _LIBCPP___EXCEPTION_TERMINATE_H
#define __EXCEPTION__

namespace std {
  [[noreturn, gnu::cold]] void terminate() noexcept;
}

namespace std {
	using terminate_handler = void(*)();
	terminate_handler set_terminate(terminate_handler) noexcept;
	terminate_handler get_terminate() noexcept;
}

#endif


namespace sl {
	using std::terminate;

	using std::terminate_handler;
	using std::set_terminate;
	using std::get_terminate;
}