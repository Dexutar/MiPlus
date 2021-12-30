# Sources
SET(NETWORK_SOURCES ConnectionManager.cpp)


# Library Target
add_library(network STATIC ${NETWORK_SOURCES})

target_include_directories(network PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Sub directories
add_subdirectory(base)
add_subdirectory(error)
add_subdirectory(packet)
add_subdirectory(protocol)
add_subdirectory(session)
add_subdirectory(types)