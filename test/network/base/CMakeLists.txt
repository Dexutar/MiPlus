# Sources
SET(BASE_TEST_SOURCES MatchConditionsTest.cpp)


# Dependencies
SET(PRIVATE_LIBRARIES network
                      GTest::gtest_main 
                      GTest::gmock_main
)


add_executable(network_base_tests ${BASE_TEST_SOURCES})

target_include_directories(network_base_tests PRIVATE ${PROJECT_SOURCE_DIR}/src/network/types/testing)
target_link_libraries(network_base_tests PRIVATE ${PRIVATE_LIBRARIES})

gtest_discover_tests(network_base_tests)