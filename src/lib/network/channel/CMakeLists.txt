# Sources
SET(NETWORK_CHANNEL_SOURCES  Channel.cpp)


# Target
target_include_directories(network_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(network_lib PRIVATE ${NETWORK_CHANNEL_SOURCES})