#pragma once
#include "streamline/metaprogramming/invoke_result.hpp"
#include "streamline/metaprogramming/type_traits/relationships.hpp"


#if __has_builtin(__builtin_invoke)
namespace sl {
	template<typename Fn, typename... Args>
	requires traits::is_invocable_v<Fn, Args...>
	constexpr invoke_result_t<Fn, Args...> invoke(Fn&& fn, Args&&... args) 
	noexcept(traits::is_noexcept_invocable_v<Fn, Args...>) {
		return __builtin_invoke(forward<Fn>(fn), forward<Args>(args)...);
	}


	template<typename R, typename Fn, typename... Args>
	requires traits::is_invocable_r_v<R, Fn, Args...>
	constexpr R invoke_r(Fn&& fn, Args&&... args) 
	noexcept(traits::is_noexcept_invocable_r_v<R, Fn, Args...>) {
		if constexpr (traits::is_same_as_v<void, remove_cv_t<R>>)
			invoke(forward<Fn>(fn), forward<Args>(args)...);
		else
			return invoke(forward<Fn>(fn), forward<Args>(args)...);
	}
}

#else 
#error TODO: invoke_result when __builtin_invoke is not present
#endif