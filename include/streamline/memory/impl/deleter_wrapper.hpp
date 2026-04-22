#pragma once
#include "streamline/functional/functor/default_delete.hpp"
#include "streamline/functional/invoke.hpp"
#include "streamline/metaprogramming/forward.hpp"
#include "streamline/metaprogramming/type_modifiers.hpp"
#include "streamline/metaprogramming/type_traits/supported_operations.hpp"


namespace sl::impl {
	template<typename PointerT>
	struct virtual_deleter_base {
		constexpr virtual void destroy(PointerT p) noexcept = 0;
		constexpr virtual void* get_ptr_to_deleter() noexcept = 0;
		constexpr virtual void const* get_ptr_to_deleter() const noexcept = 0;
		constexpr virtual ~virtual_deleter_base() noexcept = default;
	};

	template<typename PointerT, typename DeleterT>
	struct virtual_deleter : virtual_deleter_base<PointerT> {
		[[no_unique_address]] DeleterT deleter;

		template<typename D>
		constexpr virtual_deleter(D&& d) : 
			deleter{::sl::forward<D>(d)} {}

		constexpr virtual void destroy(PointerT p) noexcept override {
			return sl::invoke_r<void>(deleter, p);
		}

		inline virtual void* get_ptr_to_deleter() noexcept override {
			return static_cast<void*>(&deleter);
		}

		inline virtual void const* get_ptr_to_deleter() const noexcept override {
			return static_cast<void const*>(&deleter);
		}
	};
}


namespace sl::impl {
	template<typename PointerT, typename DeleterT>
	struct deleter_wrapper {
		[[no_unique_address]] DeleterT deleter;


		constexpr deleter_wrapper(deleter_wrapper&&) noexcept = default;
		constexpr deleter_wrapper(deleter_wrapper const&) noexcept = default;
		constexpr deleter_wrapper& operator=(deleter_wrapper&&) noexcept = default;
		constexpr deleter_wrapper& operator=(deleter_wrapper const&) noexcept = default;

		constexpr deleter_wrapper()
		noexcept(sl::traits::is_noexcept_default_constructible_v<DeleterT>)
		requires(sl::traits::is_default_constructible_v<DeleterT>) :
			deleter{} {}

		template<typename D>
		constexpr deleter_wrapper(D&& d) 
		noexcept(sl::traits::is_forwarded_noexcept_constructible_from_v<DeleterT, D>)
		requires(sl::traits::is_forwarded_constructible_from_v<DeleterT, D>) :
			deleter{::sl::forward<D>(d)} {} 

		template<typename P>
		constexpr void operator()(this auto&& self, P&& p) noexcept {
			return sl::invoke_r<void>(sl::forward_like<decltype(self)>(self.deleter), sl::forward<P>(p));
		}

		constexpr void clear() noexcept {}

		constexpr DeleterT& get_deleter() noexcept {
			return deleter;
		}

		constexpr DeleterT const& get_deleter() const noexcept {
			return deleter;
		}
		
		template<typename Deleter>
		constexpr Deleter* get_deleter_static() noexcept {
			return &deleter;
		}
	};
}

namespace sl::impl {
	template<typename PointerT>
	struct deleter_wrapper<PointerT, void> {
		virtual_deleter_base<PointerT>* deleter_ptr;

		using default_deleter_type = sl::functor::default_delete<sl::remove_pointer_t<PointerT>>;

		constexpr deleter_wrapper<void>(deleter_wrapper&&) noexcept = default;
		constexpr deleter_wrapper<void>(deleter_wrapper const&) noexcept = default;
		constexpr deleter_wrapper& operator=(deleter_wrapper&&) noexcept = default;
		constexpr deleter_wrapper& operator=(deleter_wrapper const&) noexcept = default;

		constexpr deleter_wrapper<void>() noexcept :
			deleter_ptr{new virtual_deleter<PointerT, default_deleter_type>{default_deleter_type{}}} {}

		template<typename D>
		constexpr deleter_wrapper<void>(D&& d) noexcept :
			deleter_ptr{new virtual_deleter<PointerT, remove_cvref_t<D>>{::sl::forward<D>(d)}} {}

		template<typename P>
		constexpr void operator()(P&& p) const noexcept {
			deleter_ptr->destroy(::sl::forward<P>(p));
		}

		constexpr void clear() noexcept {
			if(!deleter_ptr) return;
			delete deleter_ptr;
			deleter_ptr = nullptr;
		}


		template<typename Deleter>
		constexpr Deleter* get_deleter_static() noexcept {
			return static_cast<Deleter*>(deleter_ptr->get_ptr_to_deleter());
		}

		template<typename Deleter>
		constexpr Deleter const* get_deleter_static() const noexcept {
			return static_cast<Deleter const*>(deleter_ptr->get_ptr_to_deleter());
		}
	};
}