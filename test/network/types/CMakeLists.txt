include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src/network/types/testing)

SET(NETWORK_TYPE_TEST_SOURCES RawTypeTests.cpp
                              VarNumberTests.cpp
                              VarStringTests.cpp
                              )

add_executable(NetworkTypeTests ${NETWORK_TYPE_TEST_SOURCES})
target_link_libraries(NetworkTypeTests network GTest::gtest_main GTest::gmock_main)

gtest_discover_tests(NetworkTypeTests)