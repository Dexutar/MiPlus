cmake_minimum_required(VERSION 3.20)

project(Minecraft-Cpp-Server  VERSION 1.0
                              DESCRIPTION "A cpp Minecraft server"
                              LANGUAGES CXX)

enable_testing()

find_package (Boost 1.75 REQUIRED)
find_package (Threads REQUIRED)
find_package (GTest REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(spike/asio)