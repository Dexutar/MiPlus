include_directories(${CMAKE_CURRENT_SOURCE_DIR})

SET(NETWORK_TYPE_TEST_SOURCES VarNumberTests.cpp
                              BasicTypesTests.cpp
                              )

add_executable(network_type_tests ${NETWORK_TYPE_TEST_SOURCES})
target_link_libraries(network_type_tests network GTest::gtest_main)

gtest_discover_tests(network_type_tests)