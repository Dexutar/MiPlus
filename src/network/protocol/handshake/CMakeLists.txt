# Sources
SET(NETWORK_PROTOCOL_HANDSHAKE_SOURCES  HandshakeProtocol.cpp)


target_sources(network PRIVATE ${NETWORK_PROTOCOL_HANDSHAKE_SOURCES})
target_include_directories(network PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})