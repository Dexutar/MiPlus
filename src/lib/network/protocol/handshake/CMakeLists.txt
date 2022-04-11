# Sources
SET(NETWORK_PROTOCOL_HANDSHAKE_SOURCES  HandshakeProtocol.cpp)


# Target
target_include_directories(network_lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(network_lib PRIVATE ${NETWORK_PROTOCOL_HANDSHAKE_SOURCES})
