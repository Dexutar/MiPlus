include_directories(types)

SET(NETWORK_TYPE_TEST_SOURCES types/VarNumberTests.cpp)

add_executable(network_type_tests ${NETWORK_TYPE_TEST_SOURCES})
target_link_libraries(network_type_tests GTest::gtest_main)

gtest_discover_tests(network_type_tests)