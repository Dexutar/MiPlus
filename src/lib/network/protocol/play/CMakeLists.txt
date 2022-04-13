# Sources
SET(NETWORK_PLAY_STATUS_SOURCES PlayProtocol.cpp)


# Target
target_include_directories(network_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(network_lib PRIVATE ${NETWORK_PLAY_STATUS_SOURCES})
