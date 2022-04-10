# Sources
SET(BASE_TEST_SOURCES MatchConditionsTest.cpp)


# Dependencies
SET(PRIVATE_LIBRARIES network
                      GTest::gtest_main 
                      GTest::gmock_main
)


add_executable(NetworkBaseTests ${BASE_TEST_SOURCES})

target_include_directories(NetworkBaseTests PRIVATE ${PROJECT_SOURCE_DIR}/src/network/types/testing)
target_link_libraries(NetworkBaseTests PRIVATE ${PRIVATE_LIBRARIES})

gtest_discover_tests(NetworkBaseTests)