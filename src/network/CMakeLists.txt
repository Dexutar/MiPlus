include_directories(base)
include_directories(protocol)
include_directories(protocol/handshake)
include_directories(packet)
include_directories(packet/handshake/client)
include_directories(types)
include_directories(session)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

SET(NETWORK_SOURCES base/EventLoop.cpp
                    base/Channel.cpp
                    base/Bootstrap.cpp
                    session/Session.cpp
                    session/SessionRegistry.cpp
                    types/VarNumber.cpp
                    types/VarString.cpp
                    packet/handshake/client/HandshakePacket.cpp
                    protocol/handshake/HandshakeProtocol.cpp     
                    ConnectionManager.cpp
                    ) 

add_library(network STATIC ${NETWORK_SOURCES})

target_include_directories(network INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR}/base
                                              ${CMAKE_CURRENT_SOURCE_DIR}/protocol
                                              ${CMAKE_CURRENT_SOURCE_DIR}/protocol/handshake
                                              ${CMAKE_CURRENT_SOURCE_DIR}/packet
                                              ${CMAKE_CURRENT_SOURCE_DIR}/packet/handshake/client
                                              ${CMAKE_CURRENT_SOURCE_DIR}/session
                                              ${CMAKE_CURRENT_SOURCE_DIR}/types
                                              ${CMAKE_CURRENT_SOURCE_DIR})