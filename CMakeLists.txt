cmake_minimum_required(VERSION 3.16)

project(Minecraft-Cpp-Server  VERSION 1.0
                              DESCRIPTION "A cpp Minecraft server"
                              LANGUAGES CXX)

find_package (Boost 1.73 REQUIRED)
find_package (Threads REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)
add_subdirectory(spike/asio)