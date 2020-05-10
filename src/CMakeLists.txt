# Libraries
add_subdirectory(network)

# Main Target
add_executable(server main.cpp)

# Link libraries
target_link_libraries (server ${CMAKE_THREAD_LIBS_INIT})