cmake_minimum_required(VERSION 3.25)

project(streamline VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON")
option(BUILD_SHARED_LIBS "" ON)


### sources ###
set(${PROJECT_NAME}_HEADER_FILES
	"algorithm/aligned_to.hpp"
	"algorithm/lookup_table_hash.hpp"
	"algorithm/minmax.hpp"


	"containers/impl/array_data.hpp"
	"containers/impl/hash_table.hpp"
	"containers/impl/make_from_container.hpp"
	"containers/impl/make_from_value.hpp"
	"containers/impl/make_in_place.hpp"
	"containers/impl/seed_or_index.hpp"
	"containers/impl/tuple.hpp"

	"containers/array.fwd.hpp"
	"containers/array.hpp"
	"containers/array.inl"
	"containers/array.universal.inl"
	"containers/initializer_list.hpp"
	"containers/initializer_list.inl"
	"containers/lookup_table.fwd.hpp"
	"containers/lookup_table.hpp"
	"containers/lookup_table.inl"
	"containers/lookup_table.universal.inl"
	"containers/key_value_pair.fwd.hpp"
	"containers/key_value_pair.hpp"
	"containers/key_value_pair.inl"
	"containers/tuple.fwd.hpp"
	"containers/tuple.hpp"
	"containers/tuple.inl"
	"containers/generic_container_template_args.def.hpp"


	"diagnostics/abort.hpp"
	"diagnostics/result.hpp"
	"diagnostics/terminate.hpp"
	"diagnostics/unreachable.hpp"


	"functional/functor/address_of.hpp"
	"functional/functor/comparison.hpp"
	"functional/functor/construct_using.hpp"
	"functional/functor/default_construct.hpp"
	"functional/functor/default_delete.hpp"
	"functional/functor/forward_construct.hpp"
	"functional/functor/generic_stateless.hpp"
	"functional/functor/identity_index.hpp"
	"functional/functor/identity.hpp"
	"functional/functor/invoke_each_result.hpp"
	"functional/functor/invoke_each.hpp"
	"functional/functor/subscript.hpp"
	"functional/invoke.hpp"


	"memory/align_value.hpp"
	"memory/delete.hpp"
	"memory/launder.hpp"
	"memory/new_handler.hpp"
	"memory/new.hpp"
	"memory/start_lifetime_as.hpp"


	"metaprogramming/impl/compounded_categories.hpp"
	"metaprogramming/impl/isolated_categories.hpp"
	"metaprogramming/impl/modifiers.hpp"
	"metaprogramming/impl/relationships.hpp"

	"metaprogramming/type_traits/compounded_categories.hpp"
	"metaprogramming/type_traits/extensions.hpp"
	"metaprogramming/type_traits/isolated_categories.hpp"
	"metaprogramming/type_traits/relationships.hpp"
	"metaprogramming/type_traits/supported_operations.hpp"

	"metaprogramming/common_type.hpp"
	"metaprogramming/conditional.hpp"
	"metaprogramming/container_traits.fwd.hpp"
	"metaprogramming/container_traits.hpp"
	"metaprogramming/declval.hpp"
	"metaprogramming/empty_t.hpp"
	"metaprogramming/forward.hpp"
	"metaprogramming/in_place.hpp"
	"metaprogramming/integer_sequence.hpp"
	"metaprogramming/constant.hpp"
	"metaprogramming/invoke_return_type.hpp"
	"metaprogramming/move.hpp"
	"metaprogramming/pack_indices_of_type.hpp"
	"metaprogramming/tuple_traits.fwd.hpp"
	"metaprogramming/tuple_traits.hpp"
	"metaprogramming/type_identity.hpp"
	"metaprogramming/type_modifiers.hpp"
	"metaprogramming/type_of_pack_element.hpp"
	"metaprogramming/underlying_type.hpp"


	"numeric/impl/numeric_traits_base.hpp"

	"numeric/int.hpp"
	"numeric/numeric_traits.hpp"


	"universal/get.hpp"
	"universal/make_deduced.hpp"
	"universal/make.hpp"
	"universal/swap.hpp"
)

set(${PROJECT_NAME}_STD_HEADER_FILES
	"array"
	"atomic"
	"cassert"
	"cstddef"
	"cstdint"
	"cstdio"
	"cstdlib"
	"cstring"
	"exception"
	"new"
	"functional"
	"initializer_list"
	"iosfwd"
	"limits"
	"memory"
	"stdexcept"
	"string"
	"tuple"
	"type_traits"
	"utility"
	"version"
)

set(${PROJECT_NAME}_SOURCE_FILES
	"memory/delete.cpp"
	"memory/new.cpp"
)


### targets ###
list(TRANSFORM ${PROJECT_NAME}_HEADER_FILES PREPEND "include/${PROJECT_NAME}/")
list(TRANSFORM ${PROJECT_NAME}_STD_HEADER_FILES PREPEND "include/c++/scl/")
list(TRANSFORM ${PROJECT_NAME}_SOURCE_FILES PREPEND "src/${PROJECT_NAME}/")

#set(LIBRARY_TYPE INTERFACE)
#add_library(${PROJECT_NAME} INTERFACE)
set(LIBRARY_TYPE PUBLIC)
add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCE_FILES})
target_sources(${PROJECT_NAME} ${LIBRARY_TYPE} FILE_SET ${PROJECT_NAME}_HEADERS TYPE HEADERS BASE_DIRS "include" FILES ${${PROJECT_NAME}_HEADER_FILES})
target_sources(${PROJECT_NAME} ${LIBRARY_TYPE} FILE_SET ${PROJECT_NAME}_STD_HEADERS TYPE HEADERS BASE_DIRS "include" FILES ${${PROJECT_NAME}_STD_HEADER_FILES})

### compiler args ###
#target_compile_options(${PROJECT_NAME} ${LIBRARY_TYPE} "-march=native")
target_compile_options(${PROJECT_NAME} ${LIBRARY_TYPE} "-fno-exceptions" "-fno-rtti" "-nostdinc++" "-Wall" "-Wextra" "$<$<CONFIG:RELEASE>:-Werror>")
target_compile_options(${PROJECT_NAME} ${LIBRARY_TYPE} "$<$<CONFIG:RELEASE>:-O3>" "$<$<CONFIG:RELEASE>:-ffast-math>")
target_compile_options(${PROJECT_NAME} ${LIBRARY_TYPE} "$<$<CONFIG:DEBUG>:-O0>" "$<$<CONFIG:DEBUG>:-g>")

target_link_options(${PROJECT_NAME} ${LIBRARY_TYPE} "-nostdlib++")

### self include streamline compatibility layer directory (for 3rd party libraries) ###
cmake_path(SET SELF_INC_STD_CMAKE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/c++/scl")
file(TO_NATIVE_PATH "${SELF_INC_STD_CMAKE_DIR}" SELF_INC_STD_DIR)
target_include_directories(${PROJECT_NAME} SYSTEM AFTER ${LIBRARY_TYPE} "${SELF_INC_STD_DIR}")
message(STATUS "Including self std directory: ${SELF_INC_STD_DIR}")




### test executables ###
#add_subdirectory(test)

### install ###
install(TARGETS ${PROJECT_NAME} FILE_SET ${PROJECT_NAME}_HEADERS)
install(TARGETS ${PROJECT_NAME} FILE_SET ${PROJECT_NAME}_STD_HEADERS)
