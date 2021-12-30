# Sources
SET(NETWORK_PROTOCOL_STATUS_SOURCES StatusProtocol.cpp)


target_sources(network PRIVATE ${NETWORK_PROTOCOL_STATUS_SOURCES})
target_include_directories(network PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})