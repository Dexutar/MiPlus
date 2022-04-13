# Sources
SET(CHANNEL_TEST_SOURCES ValidFrameConditionTest.cpp)


# Dependencies
SET(PRIVATE_LIBRARIES network_lib
                      network_type_mocks
                      GTest::gtest_main 
                      GTest::gmock_main
)


# Target
add_executable(NetworkChannelTests ${CHANNEL_TEST_SOURCES})

target_include_directories(NetworkChannelTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(NetworkChannelTests PRIVATE ${PRIVATE_LIBRARIES})


# Tests
gtest_discover_tests(NetworkChannelTests)