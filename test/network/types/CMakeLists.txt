# Sources
SET(NETWORK_TYPE_TEST_SOURCES RawTypeTests.cpp
                              VarNumberTests.cpp
                              VarStringTests.cpp
)


add_executable(NetworkTypeTests ${NETWORK_TYPE_TEST_SOURCES})

target_link_libraries(NetworkTypeTests PRIVATE network GTest::gtest_main GTest::gmock_main)
target_include_directories(NetworkTypeTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/src/network/types/testing)

gtest_discover_tests(NetworkTypeTests)