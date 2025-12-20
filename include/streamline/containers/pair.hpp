#pragma once

namespace sl {
	template<typename T1, typename T2>
	struct pair {
		T1 first;
		T2 second;
	public:
		using first_type = T1;
		using second_type = T2;
	public:
		//TODO: assignment operator & constructor
	};
}