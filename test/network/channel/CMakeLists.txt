# Sources
SET(CHANNEL_TEST_SOURCES ValidFrameConditionTest.cpp)


# Dependencies
SET(PRIVATE_LIBRARIES network_lib
                      network_type_mocks
                      GTest::gtest_main 
                      GTest::gmock_main
)


# Target
add_executable(ChannelTests ${CHANNEL_TEST_SOURCES})

target_include_directories(ChannelTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ChannelTests PRIVATE ${PRIVATE_LIBRARIES})


# Tests
gtest_discover_tests(ChannelTests)