include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src/network/types)

SET(NETWORK_TYPE_TEST_SOURCES VarNumberTests.cpp
                              ${CMAKE_SOURCE_DIR}/src/network/types/VarNumber.cpp
                              )

add_executable(network_type_tests ${NETWORK_TYPE_TEST_SOURCES})
target_include_directories(network_type_tests INTERFACE ${CMAKE_SOURCE_DIR}/src/network/types)
target_link_libraries(network_type_tests GTest::gtest_main)

gtest_discover_tests(network_type_tests)