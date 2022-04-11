# Sources
SET(NETWORK_SOURCES ConnectionManager.cpp)


# Dependencies
SET(PRIVATE_LIBRARIES Boost::headers)


# Target
add_library(network_lib STATIC ${NETWORK_SOURCES})

set_target_properties(network_lib PROPERTIES OUTPUT_NAME "network")

target_include_directories(network_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(network_lib PRIVATE ${PRIVATE_LIBRARIES})


# Sub directories
add_subdirectory(base)
add_subdirectory(error)
add_subdirectory(packet)
add_subdirectory(protocol)
add_subdirectory(session)
add_subdirectory(types)