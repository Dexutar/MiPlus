# Target
target_include_directories(network_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


# Sub directories
add_subdirectory(handshake)
add_subdirectory(login)
add_subdirectory(play)
add_subdirectory(status)