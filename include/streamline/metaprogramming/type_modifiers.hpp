#pragma once
#include "streamline/metaprogramming/conditional.hpp"
#include "streamline/metaprogramming/type_identity.hpp"

#include "streamline/metaprogramming/impl/modifiers.hpp"


//cv modifiers
namespace sl {	
	template<typename T> struct remove_const          : type_identity<T> {};
	template<typename T> struct remove_const<const T> : type_identity<T> {};
	
	template<typename T> struct remove_volatile             : type_identity<T> {};
	template<typename T> struct remove_volatile<volatile T> : type_identity<T> {};

	template<typename T> struct remove_cv                   : type_identity<T> {};
	template<typename T> struct remove_cv<const          T> : type_identity<T> {};
	template<typename T> struct remove_cv<      volatile T> : type_identity<T> {};
	template<typename T> struct remove_cv<const volatile T> : type_identity<T> {};


	template<typename T> struct add_const    : type_identity<const          T> {};
	template<typename T> struct add_volatile : type_identity<      volatile T> {};
	template<typename T> struct add_cv       : type_identity<const volatile T> {};


	template<typename SrcT, typename DstT> struct copy_const                   : type_identity<DstT> {};
	template<typename SrcT, typename DstT> struct copy_const<const SrcT, DstT> : type_identity<const DstT> {};

	template<typename SrcT, typename DstT> struct copy_volatile                      : type_identity<DstT> {};
	template<typename SrcT, typename DstT> struct copy_volatile<volatile SrcT, DstT> : type_identity<volatile DstT> {};

	template<typename SrcT, typename DstT> struct copy_cv                            : type_identity<DstT> {};
	template<typename SrcT, typename DstT> struct copy_cv<const          SrcT, DstT> : type_identity<const          DstT> {};
	template<typename SrcT, typename DstT> struct copy_cv<      volatile SrcT, DstT> : type_identity<      volatile DstT> {};
	template<typename SrcT, typename DstT> struct copy_cv<const volatile SrcT, DstT> : type_identity<const volatile DstT> {};
}


//reference modifiers
namespace sl {
	template<typename T> struct remove_reference      : type_identity<T> {};
	template<typename T> struct remove_reference<T&>  : type_identity<T> {};
	template<typename T> struct remove_reference<T&&> : type_identity<T> {};


	template<typename T> struct add_lvalue_reference : decltype(impl::add_lvalue_reference<T>(0)) {};
	template<typename T> struct add_rvalue_reference : decltype(impl::add_rvalue_reference<T>(0)) {};


	template<typename SrcT, typename DstT> struct copy_reference               : type_identity<typename remove_reference<DstT>::type  > {};
	template<typename SrcT, typename DstT> struct copy_reference<SrcT& , DstT> : type_identity<typename remove_reference<DstT>::type& > {}; 
	template<typename SrcT, typename DstT> struct copy_reference<SrcT&&, DstT> : type_identity<typename remove_reference<DstT>::type&&> {};

	//TODO:
	//unwrap_reference
	//decay_unwrap_reference
}


//pointer modifiers
namespace sl {
	template<typename T> struct remove_pointer                    : type_identity<T> {};
	template<typename T> struct remove_pointer<T*               > : type_identity<T> {};
	template<typename T> struct remove_pointer<T* const         > : type_identity<T> {};
	template<typename T> struct remove_pointer<T*       volatile> : type_identity<T> {};
	template<typename T> struct remove_pointer<T* const volatile> : type_identity<T> {};
	
	template<typename T> struct add_pointer : decltype(impl::add_pointer<T>(0)) {};
}


//compound modifiers
namespace sl {
	template<typename T> struct remove_cvref : type_identity<typename remove_cv<typename remove_reference<T>::type>::type> {};

	template<typename T>
	struct decay : remove_cvref<
		T
	> {}; //TODO

	template<typename SrcT, typename DstT> struct copy_cvref : copy_reference<SrcT,
		typename copy_cv<typename remove_reference<SrcT>::type, typename remove_reference<DstT>::type>::type
	> {};
}


//array modifiers
namespace sl {

}


//sign modifiers
namespace sl {
	template<typename T> struct as_signed : copy_cv<T, typename impl::integer_type_with_size<true, sizeof(typename remove_cv<T>::type)>::type> {};
	template<typename T> struct as_unsigned : copy_cv<T, typename impl::integer_type_with_size<true, sizeof(typename remove_cv<T>::type)>::type> {};
}



//helper aliases (*_t)
namespace sl {
	//cv modifiers
	template<typename T> using remove_const_t    = typename remove_const<T>::type;
	template<typename T> using remove_volatile_t = typename remove_volatile<T>::type;
	template<typename T> using remove_cv_t       = typename remove_cv<T>::type;

	template<typename T> using add_const_t    = typename add_const<T>::type;
	template<typename T> using add_volatile_t = typename add_volatile<T>::type;
	template<typename T> using add_cv_t       = typename add_cv<T>::type;

	template<typename SrcT, typename DstT> using copy_const_t = typename copy_const<SrcT, DstT>::type;
	template<typename SrcT, typename DstT> using copy_volatile_t = typename copy_volatile<SrcT, DstT>::type;
	template<typename SrcT, typename DstT> using copy_cv_t = typename copy_cv<SrcT, DstT>::type;


	//reference modifiers
	template<typename T> using remove_reference_t = typename remove_reference<T>::type;

	template<typename T> using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;
	template<typename T> using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

	template<typename SrcT, typename DstT> using copy_reference_t = typename copy_reference<SrcT, DstT>::type;


	//pointer modifiers
	template<typename T> using remove_pointer_t = typename remove_pointer<T>::type;

	template<typename T> using add_pointer_t = typename add_pointer<T>::type;


	//compund modifiers
	template<typename T> using remove_cvref_t = typename remove_cvref<T>::type;

	template<typename T> using decay_t = typename decay<T>::type;

	template<typename SrcT, typename DstT> using copy_cvref_t = typename copy_cvref<SrcT, DstT>::type;


	//array modifiers


	//sign modifiers
	template<typename T> using as_signed_t = as_signed<T>::type;
	template<typename T> using as_unsigned_t = as_unsigned<T>::type;
}