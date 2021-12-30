cmake_minimum_required(VERSION 3.20)

project(MiPlus  VERSION 1.0
                DESCRIPTION "A cpp Minecraft server"
                LANGUAGES CXX)

find_package (Boost 1.75 REQUIRED)
find_package (Threads REQUIRED)
find_package (GTest REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-fconcepts-diagnostics-depth=2)

option(ENABLE_COVERAGE "Enable coverage" OFF)

if (ENABLE_COVERAGE)
  add_compile_options(--coverage -O0)
  add_link_options(--coverage)
endif()

enable_testing()

add_subdirectory(src)
add_subdirectory(test)