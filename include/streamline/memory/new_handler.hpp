#pragma once

namespace sl { // purposefully not versioned
	using new_handler_type = void(*)();

	namespace impl {
		inline new_handler_type& new_handler() noexcept {
			static constinit new_handler_type new_handler = nullptr;
			return new_handler; 
		}
	}
} 

namespace sl {
	inline constexpr new_handler_type set_new_handler(new_handler_type handler) noexcept { 
		return __atomic_exchange_n(&impl::new_handler(), handler, __ATOMIC_SEQ_CST); 
	}

	inline constexpr new_handler_type get_new_handler() noexcept { 
		return __atomic_load_n(&impl::new_handler(), __ATOMIC_SEQ_CST);
	}
}