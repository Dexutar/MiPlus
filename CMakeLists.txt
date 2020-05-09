cmake_minimum_required(VERSION 3.16)

project(Minecraft-Cpp-Server  VERSION 1.0
                              DESCRIPTION "A cpp Minecraft server"
                              LANGUAGES CXX)

find_package(Boost 1.73)

add_executable(server ./src/main.cpp)