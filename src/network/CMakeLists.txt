include_directories(base)

SET(NETWORK_SOURCES base/EventLoop.cpp
                    base/Channel.cpp                
                    ) 

add_library(network STATIC ${NETWORK_SOURCES})

target_include_directories(network INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/base)