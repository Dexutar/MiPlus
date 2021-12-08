include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src/network/types/testing)

SET(PACKET_TEST_SOURCES HandshakePacketTest.cpp
                        PingPacketTest.cpp
                        PongPacketTest.cpp
                        )

add_executable(PacketTests ${PACKET_TEST_SOURCES})
target_link_libraries(PacketTests network GTest::gtest_main GTest::gmock_main)

gtest_discover_tests(PacketTests)