# Sources
SET(NETWORK_BASE_SOURCES  Bootstrap.cpp
                          EventLoop.cpp
)


# Target
target_include_directories(network_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(network_lib PRIVATE ${NETWORK_BASE_SOURCES})