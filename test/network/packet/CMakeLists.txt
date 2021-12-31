# Sources
SET(PACKET_TEST_SOURCES HandshakePacketTest.cpp
                        PingPacketTest.cpp
                        PongPacketTest.cpp
                        ResponsePacketTest.cpp
)

add_executable(PacketTests ${PACKET_TEST_SOURCES})

target_link_libraries(PacketTests PRIVATE network GTest::gtest_main GTest::gmock_main)
target_include_directories(PacketTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/src/network/types/testing)

gtest_discover_tests(PacketTests)