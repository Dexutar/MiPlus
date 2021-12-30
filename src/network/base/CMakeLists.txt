# Sources
SET(NETWORK_BASE_SOURCES  Bootstrap.cpp
                          Channel.cpp
                          EventLoop.cpp
)


target_sources(network PRIVATE ${NETWORK_BASE_SOURCES})
target_include_directories(network PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})