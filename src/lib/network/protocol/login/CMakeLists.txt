# Sources
SET(NETWORK_LOGIN_STATUS_SOURCES LoginProtocol.cpp)


# Target
target_include_directories(network_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(network_lib PRIVATE ${NETWORK_LOGIN_STATUS_SOURCES})
