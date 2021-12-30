# Sources
SET(NETWORK_SESSION_SOURCES Session.cpp
                            SessionRegistry.cpp
)


target_sources(network PRIVATE ${NETWORK_SESSION_SOURCES})
target_include_directories(network PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})