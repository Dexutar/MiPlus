# Targets
add_executable(chat-server tcp-chat-server.cpp)

# Link libraries
target_link_libraries (chat-server ${CMAKE_THREAD_LIBS_INIT})