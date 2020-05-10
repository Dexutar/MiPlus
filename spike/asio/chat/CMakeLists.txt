# Targets
add_executable(chat_server chat_server.cpp chat_message.hpp)
add_executable(chat_client chat_client.cpp chat_message.hpp)

# Link libraries
target_link_libraries (chat_server ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (chat_client ${CMAKE_THREAD_LIBS_INIT})
