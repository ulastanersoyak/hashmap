cmake_minimum_required(VERSION 3.22)

if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 23)
endif()

project(
  project_name
  VERSION 0.0.0
  LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(
  -Wall
  -Wextra
  -Wpedantic
  -Werror
  -Wunused
  -Wuninitialized
  -Wshadow
  -Wconversion
  -Wduplicated-cond
  -Wduplicated-branches
  -Wlogical-op
  -Wuseless-cast
  -Wsign-conversion
  -Wfloat-equal
  -Weffc++
  -Wold-style-cast
  -Wvexing-parse
  -Wformat=2
  -Wvla
  -Wsuggest-override
  -Wsuggest-final-methods
  -Wsuggest-final-types
  -Wnon-virtual-dtor
  -Wctor-dtor-privacy
  -Wnrvo)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(
    -Wweak-vtables
    -Wglobal-constructors
    -Wexit-time-destructors
    -Wused-but-marked-unused
    -Wcovered-switch-default
    -Wmissing-prototypes
    -Woverloaded-virtual
    -Wdelete-non-virtual-dtor)
endif()

set(CMAKE_BUILD_TYPE Debug)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
  add_compile_options(-g)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Release)
  add_compile_options(-Ofast)
endif()

include_directories(${CMAKE_SOURCE_DIR})

add_executable(test_ct_hashmap test/ute_hashmap.test.cpp)
target_include_directories(test_ct_hashmap PRIVATE ${CMAKE_SOURCE_DIR})
