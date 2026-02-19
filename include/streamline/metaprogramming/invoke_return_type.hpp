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
	struct invoke_return_type {
		constexpr static bool __is_noexcept = false;
	};


	template<typename FnT, typename... ArgTs> requires requires { __builtin_invoke(declval<FnT>(), declval<ArgTs>()...); }
	struct invoke_return_type<FnT, ArgTs...> : type_identity<decltype(__builtin_invoke(declval<FnT>(), declval<ArgTs>()...))> {
		constexpr static bool __is_noexcept = noexcept(__builtin_invoke(declval<FnT>(), declval<ArgTs>()...));
	};
}

#else 
#error TODO: invoke_return_type when __builtin_invoke is not present
#endif


namespace sl {
	namespace impl {
		template<typename FnT, typename TupleT, index_t I>
		constexpr bool has_invoke_return_type = requires {
			typename invoke_return_type<FnT, typename tuple_traits<remove_cvref_t<TupleT>>::template type_of_element<I>, index_constant_type<I>>::type;
		};

		template<typename FnT, typename TupleT, typename>
		struct invoke_each_return_type {
			constexpr static bool __is_noexcept = false;
		};

		template<typename FnT, typename TupleT, index_t... Is> requires (has_invoke_return_type<FnT, TupleT, Is> && ...)
		struct invoke_each_return_type<FnT, TupleT, index_sequence_type<Is...>> : common_type<typename invoke_return_type<FnT, typename tuple_traits<remove_cvref_t<TupleT>>::template type_of_element<Is>, index_constant_type<Is>>::type...> {
			constexpr static bool __is_noexcept = (invoke_return_type<FnT, typename tuple_traits<remove_cvref_t<TupleT>>::template type_of_element<Is>, index_constant_type<Is>>::__is_noexcept && ...);
		};
	}

	template<typename FnT, typename TupleT>
	using invoke_each_return_type = impl::invoke_each_return_type<FnT, TupleT, index_sequence_of_length_type<tuple_traits<remove_cvref_t<TupleT>>::size>>;
}

namespace sl {
	template<typename FnT, typename... ArgTs>
	using invoke_return_type_t = typename invoke_return_type<FnT, ArgTs...>::type;

	template<typename FnT, typename TupleT>
	using invoke_each_return_type_t = typename invoke_each_return_type<FnT, TupleT>::type;
}