# Libraries
add_subdirectory(network)

# Main Target
add_executable(server main.cpp)

# Include headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Link libraries
target_link_libraries (server PRIVATE ${CMAKE_THREAD_LIBS_INIT} network)