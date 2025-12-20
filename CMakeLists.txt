cmake_minimum_required(VERSION 3.25)

project(streamline VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON")
option(BUILD_SHARED_LIBS "" ON)


### sources ###
set(${PROJECT_NAME}_HEADER_FILES
	"algorithm/minmax.hpp"


	"containers/initializer_list.hpp"
	"containers/initializer_list.inl"


	"diagnostics/abort.hpp"
	"diagnostics/result.hpp"
	"diagnostics/terminate.hpp"
	"diagnostics/unreachable.hpp"


	"functional/comparison.hpp"
	"functional/identity_function.hpp"


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
	"metaprogramming/empty_t.hpp"
	"metaprogramming/forward.hpp"
	"metaprogramming/in_place.hpp"
	"metaprogramming/integer_sequence.hpp"
	"metaprogramming/integral_constant.hpp"
	"metaprogramming/move.hpp"
	"metaprogramming/pack_indices_of_type.hpp"
	"metaprogramming/tuple_traits.fwd.hpp"
	"metaprogramming/tuple_traits.hpp"
	"metaprogramming/type_identity.hpp"
	"metaprogramming/type_modifiers.hpp"
	"metaprogramming/type_of_pack_element.hpp"


	"numeric/impl/numeric_traits_base.hpp"

	"numeric/int.hpp"
	"numeric/numeric_traits.hpp"


	"universal/get.hpp"
	"universal/make_deduced.hpp"
	"universal/make.hpp"
)

set(${PROJECT_NAME}_STD_HEADER_FILES
	"initializer_list"
	"type_traits"
	"utility"
	"version"
)

set(${PROJECT_NAME}_SOURCE_FILES
	""
)


### targets ###
list(TRANSFORM ${PROJECT_NAME}_HEADER_FILES PREPEND "include/${PROJECT_NAME}/")
list(TRANSFORM ${PROJECT_NAME}_STD_HEADER_FILES PREPEND "include/c++/scl/")
list(TRANSFORM ${PROJECT_NAME}_SOURCE_FILES PREPEND "src/${PROJECT_NAME}/")

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCE_FILES})
target_sources(${PROJECT_NAME} PUBLIC FILE_SET ${PROJECT_NAME}_HEADERS TYPE HEADERS BASE_DIRS "include" FILES ${${PROJECT_NAME}_HEADER_FILES})
target_sources(${PROJECT_NAME} PUBLIC FILE_SET ${PROJECT_NAME}_STD_HEADERS TYPE HEADERS BASE_DIRS "include" FILES ${${PROJECT_NAME}_STD_HEADER_FILES})

### compiler args ###
#target_compile_options(${PROJECT_NAME} PUBLIC "-march=native")
target_compile_options(${PROJECT_NAME} PUBLIC "-fno-exceptions" "-fno-rtti" "-nostdinc++" "-Wall" "-Wextra" "$<$<CONFIG:RELEASE>:-Werror>")
target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:RELEASE>:-O3>" "$<$<CONFIG:RELEASE>:-ffast-math>")
target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:DEBUG>:-O0>" "$<$<CONFIG:DEBUG>:-g>")

target_link_options(${PROJECT_NAME} PUBLIC "-nostdlib++")

### self include streamline compatibility layer directory (for 3rd party libraries) ###
cmake_path(SET SELF_INC_STD_CMAKE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/c++/scl")
file(TO_NATIVE_PATH "${SELF_INC_STD_CMAKE_DIR}" SELF_INC_STD_DIR)
target_include_directories(${PROJECT_NAME} SYSTEM AFTER PUBLIC "${SELF_INC_STD_DIR}")
message(STATUS "Including self std directory: ${SELF_INC_STD_DIR}")




### test executables ###
#add_subdirectory(test)

### install ###
install(TARGETS ${PROJECT_NAME} FILE_SET ${PROJECT_NAME}_HEADERS)
install(TARGETS ${PROJECT_NAME} FILE_SET ${PROJECT_NAME}_STD_HEADERS)
