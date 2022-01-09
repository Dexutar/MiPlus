cmake_minimum_required(VERSION 3.20)


project(MiPlus  VERSION 1.0
                DESCRIPTION "A cpp Minecraft server"
                LANGUAGES CXX
)


find_package (Boost 1.75 REQUIRED)
find_package (Threads REQUIRED)
find_package (GTest REQUIRED)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


option(ENABLE_COVERAGE "Enable coverage" OFF)

add_compile_options($<$<AND:$<CONFIG:Debug>,$<BOOL:${ENABLE_COVERAGE}>,$<CXX_COMPILER_ID:GNU>>:--coverage>)
add_link_options($<$<AND:$<CONFIG:Debug>,$<BOOL:${ENABLE_COVERAGE}>,$<CXX_COMPILER_ID:GNU>>:--coverage>)

enable_testing()


add_subdirectory(src)
add_subdirectory(test)