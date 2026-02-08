#pragma once
#include "streamline/metaprogramming/common_type.hpp"
#include "streamline/metaprogramming/declval.hpp"
#include "streamline/metaprogramming/integer_sequence.hpp"
#include "streamline/metaprogramming/tuple_traits.fwd.hpp"
#include "streamline/metaprogramming/type_identity.hpp"
#include "streamline/numeric/int.hpp"

#if __has_builtin(__builtin_invoke)
namespace sl {
	template<typename FnT, typename... ArgTs>
	struct invoke_result {
		constexpr static bool __is_noexcept = false;
	};


	template<typename FnT, typename... ArgTs> requires requires { __builtin_invoke(declval<FnT>(), declval<ArgTs>()...); }
	struct invoke_result<FnT, ArgTs...> : type_identity<decltype(__builtin_invoke(declval<FnT>(), declval<ArgTs>()...))> {
		constexpr static bool __is_noexcept = noexcept(__builtin_invoke(declval<FnT>(), declval<ArgTs>()...));
	};
}

#else 
#error TODO: invoke_result when __builtin_invoke is not present
#endif


namespace sl {
	namespace impl {
		template<typename FnT, typename TupleT, index_t I>
		constexpr bool has_invoke_result = requires {
			typename invoke_result<FnT, typename tuple_traits<TupleT>::template type_of_element<I>, index_constant_type<I>>::type;
		};

		template<typename FnT, typename TupleT, typename>
		struct invoke_each_result {
			constexpr static bool __is_noexcept = false;
		};

		template<typename FnT, typename TupleT, index_t... Is> requires (has_invoke_result<FnT, TupleT, Is> && ...)
		struct invoke_each_result<FnT, TupleT, index_sequence_type<Is...>> : common_type<typename invoke_result<FnT, typename tuple_traits<TupleT>::template type_of_element<Is>, index_constant_type<Is>>::type...> {
			constexpr static bool __is_noexcept = (invoke_result<FnT, typename tuple_traits<TupleT>::template type_of_element<Is>, index_constant_type<Is>>::__is_noexcept && ...);
		};
	}

	template<typename FnT, typename TupleT>
	using invoke_each_result = impl::invoke_each_result<FnT, TupleT, index_sequence_of_length_type<tuple_traits<TupleT>::size>>;
}

namespace sl {
	template<typename FnT, typename... ArgTs>
	using invoke_result_t = typename invoke_result<FnT, ArgTs...>::type;

	template<typename FnT, typename TupleT>
	using invoke_each_result_t = typename invoke_each_result<FnT, TupleT>::type;
}