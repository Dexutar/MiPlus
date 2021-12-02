include_directories(base)
include_directories(error)
include_directories(packet)
include_directories(packet/handshake/client)
include_directories(packet/status/client)
include_directories(packet/status/server)
include_directories(protocol)
include_directories(protocol/handshake)
include_directories(protocol/status)
include_directories(session)
include_directories(types)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

SET(NETWORK_SOURCES base/EventLoop.cpp
                    base/Channel.cpp
                    base/Bootstrap.cpp
                    packet/handshake/client/HandshakePacket.cpp
                    packet/status/client/PingPacket.cpp
                    protocol/Protocol.cpp
                    protocol/handshake/HandshakeProtocol.cpp
                    protocol/status/StatusProtocol.cpp
                    session/Session.cpp
                    session/SessionRegistry.cpp
                    ConnectionManager.cpp
                    ) 

add_library(network STATIC ${NETWORK_SOURCES})

target_include_directories(network INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR}/base
                                              ${CMAKE_CURRENT_SOURCE_DIR}/packet
                                              ${CMAKE_CURRENT_SOURCE_DIR}/packet/handshake/client
                                              ${CMAKE_CURRENT_SOURCE_DIR}/packet/status/client
                                              ${CMAKE_CURRENT_SOURCE_DIR}/packet/status/server
                                              ${CMAKE_CURRENT_SOURCE_DIR}/protocol
                                              ${CMAKE_CURRENT_SOURCE_DIR}/protocol/handshake
                                              ${CMAKE_CURRENT_SOURCE_DIR}/protocol/status
                                              ${CMAKE_CURRENT_SOURCE_DIR}/session
                                              ${CMAKE_CURRENT_SOURCE_DIR}/types
                                              ${CMAKE_CURRENT_SOURCE_DIR})