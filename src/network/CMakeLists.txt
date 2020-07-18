project(network)

include_directories(base)
include_directories(protocol)
include_directories(codec)
include_directories(codec/handshake)
include_directories(handler)
include_directories(handler/handshake)
include_directories(message)
include_directories(types)
include_directories(session)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

SET(NETWORK_SOURCES base/EventLoop.cpp
                    base/Channel.cpp
                    base/Bootstrap.cpp
                    session/Session.cpp
                    session/SessionRegistry.cpp
                    types/VarNumber.cpp
                    protocol/HandshakeProtocol.cpp     
                    ConnectionManager.cpp
                    ) 

add_library(network STATIC ${NETWORK_SOURCES})

target_include_directories(network INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR}/base
                                              ${CMAKE_CURRENT_SOURCE_DIR}/protocol
                                              ${CMAKE_CURRENT_SOURCE_DIR}/handler
                                              ${CMAKE_CURRENT_SOURCE_DIR}/handler/handshake
                                              ${CMAKE_CURRENT_SOURCE_DIR}/codec
                                              ${CMAKE_CURRENT_SOURCE_DIR}/codec/handshake
                                              ${CMAKE_CURRENT_SOURCE_DIR}/message
                                              ${CMAKE_CURRENT_SOURCE_DIR}/session
                                              ${CMAKE_CURRENT_SOURCE_DIR}/types
                                              ${CMAKE_CURRENT_SOURCE_DIR})