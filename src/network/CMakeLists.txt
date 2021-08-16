include_directories(base)
include_directories(protocol)
include_directories(packet)
include_directories(packet/handshake)
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
                    packet/handshake/HandshakePacket.cpp
                    protocol/HandshakeProtocol.cpp     
                    ConnectionManager.cpp
                    ) 

add_library(network STATIC ${NETWORK_SOURCES})

target_include_directories(network INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR}/base
                                              ${CMAKE_CURRENT_SOURCE_DIR}/protocol
                                              ${CMAKE_CURRENT_SOURCE_DIR}/packet
                                              ${CMAKE_CURRENT_SOURCE_DIR}/packet/handshake
                                              ${CMAKE_CURRENT_SOURCE_DIR}/session
                                              ${CMAKE_CURRENT_SOURCE_DIR}/types
                                              ${CMAKE_CURRENT_SOURCE_DIR})