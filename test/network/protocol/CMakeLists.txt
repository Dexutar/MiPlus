# Sources
SET(PROTOCOL_TEST_SOURCES ConnectionStateTest.cpp
                          ProtocolFactoryTest.cpp
)


# Dependencies
SET(PRIVATE_LIBRARIES network_lib
                      GTest::gtest_main
)


# Target
add_executable(ProtocolTests ${PROTOCOL_TEST_SOURCES})

target_include_directories(ProtocolTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ProtocolTests PRIVATE ${PRIVATE_LIBRARIES})


# Tests
gtest_discover_tests(ProtocolTests)
