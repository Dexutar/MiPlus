cmake_minimum_required(VERSION 3.16)

project(Minecraft-Cpp-Server  VERSION 1.0
                              DESCRIPTION "A cpp Minecraft server"
                              LANGUAGES CXX)

find_package(Boost 1.73 REQUIRED)
find_package (Threads REQUIRED)

# Main Target
add_executable(server ./src/main.cpp)

# Spike targets
add_executable(chat_server ./spike/asio/chat/chat_server.cpp ./spike/asio/chat/chat_message.hpp)
add_executable(chat_client ./spike/asio/chat/chat_client.cpp ./spike/asio/chat/chat_message.hpp)

# Set C++ standard
set_property(TARGET server chat_server chat_client PROPERTY CXX_STANDARD 20)

# Link libraries
target_link_libraries (server ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (chat_server ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (chat_client ${CMAKE_THREAD_LIBS_INIT})