#pragma once
#include "streamline/containers/array.hpp"
#include "streamline/metaprogramming/forward.hpp"
#include "streamline/metaprogramming/in_place.hpp"
#include "streamline/metaprogramming/integer_sequence.hpp"
#include "streamline/numeric/int.hpp"
#include "streamline/functional/invoke.hpp"
#include "streamline/universal/make_deduced.hpp"

namespace sl::functor {
	template<typename R, auto Func>
	struct invoke_each_result {
		template<typename T, sl::index_t... Is, typename... Args>
		constexpr R operator()(sl::integer_sequence_type<T, Is...>, Args&&... args) const noexcept {
			using lambda_type = sl::invoke_return_type_t<decltype(Func), Args&&..., sl::integral_constant_type<T, 0>>(*)(Args&&...) noexcept;
			constexpr sl::array<sizeof...(Is), lambda_type> funcs{{
				[](Args&&... a) noexcept -> sl::invoke_return_type_t<decltype(Func), Args&&..., sl::integral_constant_type<T, 0>> {
					return sl::invoke(Func, sl::forward<Args>(a)..., sl::integral_constant<T, Is>);
				}...
			}};

			for(sl::index_t i = 0; i < funcs.size(); ++i)
				RESULT_VERIFY(sl::invoke(funcs[i], sl::forward<Args>(args)...));
			return {};
		};
	};
}