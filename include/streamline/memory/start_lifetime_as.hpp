#pragma once
#include "streamline/numeric/int.hpp"
#include "streamline/metaprogramming/type_traits/isolated_categories.hpp"
#include "streamline/metaprogramming/type_modifiers.hpp"
#include "streamline/memory/launder.hpp"
#include "streamline/memory/new.hpp"


namespace sl::impl {
    template<typename T, typename VoidT>
    copy_cv_t<VoidT, T>* start_lifetime_as(VoidT* p, size_t n) noexcept {
        void* mutable_p = const_cast<void*>(p);
        byte* bytes = new(mutable_p) byte[sizeof(T) * n];
        return launder(reinterpret_cast<copy_cv_t<VoidT, T>*>(bytes));
    }
}


namespace sl {
    template<traits::implicit_lifetime T>
    T* start_lifetime_as(void* p) noexcept {
		return impl::start_lifetime_as<T>(p, 1);
    }

    template<traits::implicit_lifetime T>
    T const* start_lifetime_as(void const* p) noexcept {
		return impl::start_lifetime_as<T>(p, 1);
    }

    template<traits::implicit_lifetime T>
    T volatile* start_lifetime_as(void volatile* p) noexcept {
		return impl::start_lifetime_as<T>(p, 1);
    }

    template<traits::implicit_lifetime T>
    T const volatile* start_lifetime_as(void const volatile* p) noexcept {
		return impl::start_lifetime_as<T>(p, 1);
    }
}


namespace sl {
    template<traits::implicit_lifetime T>
    T* start_lifetime_as_array(void* p, size_t n) noexcept {
		if(n == 0) return static_cast<T*>(p);
		return impl::start_lifetime_as<T>(p, n);
    }

    template<traits::implicit_lifetime T>
    T const* start_lifetime_as_array(void const* p, size_t n) noexcept {
		if(n == 0) return static_cast<T const*>(p);
		return impl::start_lifetime_as<T>(p, n);
    }

    template<traits::implicit_lifetime T>
    T volatile* start_lifetime_as_array(void volatile* p, size_t n) noexcept {
		if(n == 0) return static_cast<T volatile*>(p);
		return impl::start_lifetime_as<T>(p, n);
    }

    template<traits::implicit_lifetime T>
    T const volatile* start_lifetime_as_array(void const volatile* p, size_t n) noexcept {
		if(n == 0) return static_cast<T const volatile*>(p);
		return impl::start_lifetime_as<T>(p, n);
    }
}