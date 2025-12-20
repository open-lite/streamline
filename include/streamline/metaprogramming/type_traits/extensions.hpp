#pragma once
#include "streamline/metaprogramming/type_modifiers.hpp"


namespace sl::traits {
    template<typename T, template<typename, typename...> typename TraitT, typename... Args>
    using when_decayed = TraitT<decay_t<T>, Args...>;

    template<typename T, template<typename, typename...> typename TraitT, typename... Args>
    using when_forwarded = TraitT<T&&, Args...>;
}


//helper templates
namespace sl::traits {
    template<typename T, template<typename, typename...> typename TraitT, typename... Args>
	constexpr bool when_decayed_v = when_decayed<T, TraitT, Args...>::value;
    template<typename T, template<typename, typename...> typename TraitT, typename... Args>
	using when_decayed_t = typename when_decayed<T, TraitT, Args...>::type;

    template<typename T, template<typename, typename...> typename TraitT, typename... Args>
	constexpr bool when_forwarded_v = when_forwarded<T, TraitT, Args...>::value;
    template<typename T, template<typename, typename...> typename TraitT, typename... Args>
	using when_forwarded_t = typename when_forwarded<T, TraitT, Args...>::type;
}

//concepts
namespace sl::traits {
    template<typename T, template<typename, typename...> typename TraitT, typename... Args>
	concept decayed = when_decayed_v<T, TraitT, Args...>;

    template<typename T, template<typename, typename...> typename TraitT, typename... Args>
	concept forwarded = when_forwarded_v<T, TraitT, Args...>;
}