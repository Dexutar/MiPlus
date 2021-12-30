# Libraries
add_subdirectory(network)


# Main Target
add_executable(server main.cpp)

target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries (server PRIVATE ${CMAKE_THREAD_LIBS_INIT} network)