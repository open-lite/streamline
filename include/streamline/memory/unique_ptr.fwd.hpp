#pragma once
#include "streamline/functional/functor/default_delete.hpp"
#include "streamline/metaprogramming/constant.hpp"
#include "streamline/metaprogramming/type_traits/relationships.hpp"
#include "streamline/numeric/int.hpp"
#include "streamline/containers/generic_container_template_args.def.hpp"


namespace sl::generic {
	template<SL_GENERIC_CONTAINER_TEMPLATE_ARGS()>
	class unique_ptr;
}

namespace sl {
	template<typename T, sl::traits::noexcept_invocable_r<void, T*> DeleterT = sl::functor::default_delete<T>>
	using unique_ptr = generic::unique_ptr<T, DeleterT>;
}
