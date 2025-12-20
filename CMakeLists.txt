cmake_minimum_required(VERSION 3.25)

project(streamline VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON")
option(BUILD_SHARED_LIBS "" ON)


### sources ###
set(${PROJECT_NAME}_HEADER_FILES
	"diagnostics/abort.hpp"
	"diagnostics/result.hpp"
	"diagnostics/terminate.hpp"
	"diagnostics/unreachable.hpp"


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
	"metaprogramming/empty_t.hpp"
	"metaprogramming/in_place.hpp"
	"metaprogramming/integral_constant.hpp"
	"metaprogramming/type_identity.hpp"
	"metaprogramming/type_modifiers.hpp"


	"numeric/int.hpp"
)

set(${PROJECT_NAME}_STD_HEADER_FILES
	"version"
	"type_traits"
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
