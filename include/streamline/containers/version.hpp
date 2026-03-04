#pragma once
#include "streamline/containers/version.fwd.hpp"

#include "streamline/containers/array.hpp"
#include "streamline/numeric/int.hpp"
#include "streamline/metaprogramming/forward.hpp"
#include "streamline/metaprogramming/tuple_traits.fwd.hpp"
#include "streamline/metaprogramming/container_traits.fwd.hpp"


namespace sl::generic {
	template<traits::unsigned_integral_like T>
	struct version<T> : sl::array<4, T> {
		constexpr auto&& major(this auto&& self) noexcept { return sl::forward_like<decltype(self)>(self[0]); }
		constexpr auto&& minor(this auto&& self) noexcept { return sl::forward_like<decltype(self)>(self[1]); }
		constexpr auto&& patch(this auto&& self) noexcept { return sl::forward_like<decltype(self)>(self[2]); }
		constexpr auto&& build(this auto&& self) noexcept { return sl::forward_like<decltype(self)>(self[3]); }
	};
}

namespace sl {
	using version = generic::version<sl::uint32_t>;
}


namespace sl {
	template<traits::unsigned_integral_like T>
	struct container_traits<generic::version<T>> : container_traits<sl::array<4, T>> {};

	template<traits::unsigned_integral_like T>
	struct tuple_traits<generic::version<T>> : tuple_traits<sl::array<4, T>> {};
}



namespace sl::test {
	constexpr version v3_2_1_max{3,2,1,static_cast<typename version::value_type>(-1)};

	static_assert(v3_2_1_max.major() == 3);
	static_assert(v3_2_1_max.minor() == 2);
	static_assert(v3_2_1_max.patch() == 1);
	static_assert(v3_2_1_max.build() == static_cast<typename version::value_type>(-1));
}