cmake_minimum_required(VERSION 3.16)

project(Minecraft-Cpp-Server  VERSION 1.0
                              DESCRIPTION "A cpp Minecraft server"
                              LANGUAGES CXX)

find_package(Boost 1.73 REQUIRED)
find_package (Threads REQUIRED)

# Main Target
add_executable(server ./src/main.cpp)

# Set C++ standard
set_property(TARGET server PROPERTY CXX_STANDARD 20)

# Link libraries
target_link_libraries (server ${CMAKE_THREAD_LIBS_INIT})