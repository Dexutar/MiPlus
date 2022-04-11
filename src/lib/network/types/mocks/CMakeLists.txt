# Dependencies
SET(INTERFACE_LIBRARIES GTest::gmock_main)


# Target
add_library(network_type_mocks INTERFACE)

target_include_directories(network_type_mocks INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(network_type_mocks INTERFACE ${INTERFACE_LIBRARIES})