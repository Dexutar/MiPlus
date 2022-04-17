# Sources
SET(NETWORK_TYPE_TEST_SOURCES ConnectionStateTests.cpp
                              RawTypeTests.cpp
                              VarNumberTests.cpp
                              VarStringTests.cpp
)


# Dependencies
SET(PRIVATE_LIBRARIES network_lib
                      network_type_mocks
                      GTest::gtest_main
                      GTest::gmock_main
)


# Target
add_executable(NetworkTypeTests ${NETWORK_TYPE_TEST_SOURCES})

target_include_directories(NetworkTypeTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(NetworkTypeTests PRIVATE ${PRIVATE_LIBRARIES})

# Tests
gtest_discover_tests(NetworkTypeTests)