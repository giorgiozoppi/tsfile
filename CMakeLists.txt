cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
file(STRINGS "VERSION" VERSION_STRING)
project(tsfile VERSION "${VERSION_STRING}" LANGUAGES CXX)
set(CMAKE_BUILD_TYPE_INIT Release)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_VERBOSE_MAKEFILE 0)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
include_directories(include)
file(GLOB_RECURSE INCLUDE_FILES ${CMAKE_SOURCE_DIR}/include/tsfile/*.h ${CMAKE_SOURCE_DIR}/include/tsfile/common/*.h)
file(GLOB_RECURSE SOURCE_FILES_NO_MAIN ${CMAKE_SOURCE_DIR}/src/tsfile/*.cpp)
# for using catch we don't need the main
list(FILTER SOURCE_FILES_NO_MAIN EXCLUDE REGEX ".*main.cpp$")
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/tsfile/common/*.cpp \ 
              ${CMAKE_SOURCE_DIR}/src/tsfile/model/*.cpp \ 
              ${CMAKE_SOURCE_DIR}/src/tsfile/io/*.cpp)
add_library(tsfile STATIC ${SOURCES})
include(${CMAKE_SOURCE_DIR}/cmake/unit_test.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/clang_tools.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/cppcheck.cmake)

if(CMAKE_BUILD_TYPE MATCHES "^[Rr]elease")
include(${CMAKE_SOURCE_DIR}/cmake/doxygen.cmake)
endif()



if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  # using Clang
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(tsfile PRIVATE -Wall -Wextra -Werror -std=c++20 -stdlib=libc++ -fsanitize=address -fprofile-arcs -ftest-coverage -fno-omit-frame-pointer -v)
  else()
    target_compile_options(tsfile PRIVATE -Wall -Wextra -Werror -std=c++20 -stdlib=libc++ -v)
  endif()
  elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # using GCC
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_options(tsfile PRIVATE -Wall -Wextra -Werror -std=c++20  -fconcepts -fmodules-ts -g -O0 -fprofile-arcs -ftest-coverage)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lgcov -coverage")
  else()
  target_compile_options(tsfile PRIVATE -Wall -Wextra -Werror -std=c++20  -fconcepts -fmodules-ts)
  endif()
endif()
# TODO: Run -Werror in CI.
