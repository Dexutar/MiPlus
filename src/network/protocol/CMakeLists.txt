# Sources
SET(NETWORK_PROTOCOL_SOURCES  Protocol.cpp)


target_sources(network PRIVATE ${NETWORK_PROTOCOL_SOURCES})
target_include_directories(network PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Sub directories
add_subdirectory(handshake)
add_subdirectory(status)