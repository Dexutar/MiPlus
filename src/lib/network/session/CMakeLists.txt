# Sources
SET(NETWORK_SESSION_SOURCES Session.cpp
                            SessionRegistry.cpp
)

# Target
target_include_directories(network_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(network_lib PRIVATE ${NETWORK_SESSION_SOURCES})
