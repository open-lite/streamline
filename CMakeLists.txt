cmake_minimum_required(VERSION 3.15)

project(streamline VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON")


### sources ###
set(${PROJECT_NAME}_HEADER_FILES
    ""
)
set(${PROJECT_NAME}_SOURCE_FILES
	""
)

### compiler args ###
#target_compile_options(${PROJECT_NAME} PUBLIC "-march=native")
target_compile_options(${PROJECT_NAME} PUBLIC "-fno-rtti" "-fno-exceptions" "-fopenmp" "-Wall" "-Wextra" "$<$<CONFIG:RELEASE>:-Werror>")
target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:RELEASE>:-Werror>" "$<$<CONFIG:RELEASE>:-O3>" "$<$<CONFIG:RELEASE>:-ffast-math>")
target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:DEBUG>:-O0>" "$<$<CONFIG:DEBUG>:-g>")

### targets ###
list(TRANSFORM ${PROJECT_NAME}_HEADER_FILES PREPEND "include/${PROJECT_NAME}/")
list(TRANSFORM ${PROJECT_NAME}_SOURCE_FILES PREPEND "src/${PROJECT_NAME}/")

add_library(${PROJECT_NAME} ${PROJECT_NAME}_SOURCE_FILES)
target_sources(${PROJECT_NAME} PUBLIC FILE_SET ${PROJECT_NAME}_HEADERS TYPE HEADERS BASE_DIRS "include" FILES ${${PROJECT_NAME}_HEADER_FILES})


### self include directory ###
cmake_path(SET SELF_INC_CMAKE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
file(TO_NATIVE_PATH "${SELF_INC_CMAKE_DIR}" SELF_INC_DIR)
target_include_directories(${PROJECT_NAME} SYSTEM BEFORE INTERFACE "${SELF_INC_DIR}")
message(STATUS "Including self directory: ${SELF_INC_DIR}")


### test executables ###
#add_subdirectory(test)

### install ###
install(TARGETS ${PROJECT_NAME} FILE_SET ${PROJECT_NAME}_HEADERS)
