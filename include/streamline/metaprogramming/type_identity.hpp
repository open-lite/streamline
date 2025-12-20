#pragma once


namespace sl {
	template<typename T>
	struct type_identity { 
		using type = T; 
	};
}

namespace sl {
	template<typename T>
	using type_identity_t = typename type_identity<T>::type;
}
