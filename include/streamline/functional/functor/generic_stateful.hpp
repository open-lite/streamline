#pragma once
#include "streamline/metaprogramming/forward.hpp"
#include "streamline/containers/tuple.hpp"
#include "streamline/functional/invoke.hpp"
#include "streamline/metaprogramming/integer_sequence.hpp"


namespace sl::functor {
	template<typename FuncT, typename... StateTs>
	struct generic_stateful {
		template<typename FuncArg, typename... StateArgs>
		constexpr generic_stateful(FuncArg&& func, StateArgs&&... states) noexcept :
			f{func}, state{{states}...} {}

		template<typename... Args>
		constexpr decltype(auto) operator()(Args&&... args) noexcept {
			constexpr auto invoke_f = []<sl::index_t... Is, typename FnT, typename TupleT, typename... As>(
				sl::index_sequence_type<Is...>,
				FnT&& func,
				TupleT&& tuple,
				As&&... as
			) noexcept -> decltype(auto) {
				return sl::invoke(sl::forward<FnT>(func), sl::forward_like<TupleT>(tuple[sl::index_constant<Is>])..., sl::forward<As>(as)...);
			};

			return sl::invoke(invoke_f, sl::index_sequence_for_pack<StateTs...>, f, state, sl::forward<Args>(args)...);
		};
	
	private:
		FuncT f;
		[[no_unique_address]] sl::tuple<StateTs...> state;
	};
}
