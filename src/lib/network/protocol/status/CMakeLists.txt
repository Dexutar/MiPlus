# Sources
SET(NETWORK_PROTOCOL_STATUS_SOURCES StatusProtocol.cpp)


# Target
target_include_directories(network_lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(network_lib PRIVATE ${NETWORK_PROTOCOL_STATUS_SOURCES})
