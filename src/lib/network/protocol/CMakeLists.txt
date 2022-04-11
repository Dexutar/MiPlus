# Sources
SET(NETWORK_PROTOCOL_SOURCES  Protocol.cpp)


# Target
target_include_directories(network_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(network_lib PRIVATE ${NETWORK_PROTOCOL_SOURCES})


# Sub directories
add_subdirectory(handshake)
add_subdirectory(status)