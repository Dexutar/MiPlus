# Sources
SET(BASE_TEST_SOURCES MatchConditionsTest.cpp)


# Dependencies
SET(PRIVATE_LIBRARIES network_lib
                      network_type_mocks
                      GTest::gtest_main 
                      GTest::gmock_main
)


# Target
add_executable(NetworkBaseTests ${BASE_TEST_SOURCES})

target_include_directories(NetworkBaseTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(NetworkBaseTests PRIVATE ${PRIVATE_LIBRARIES})


# Tests
gtest_discover_tests(NetworkBaseTests)