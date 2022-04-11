# Sources
SET(PACKET_TEST_SOURCES HandshakePacketTest.cpp
                        PingPacketTest.cpp
                        PongPacketTest.cpp
                        ResponsePacketTest.cpp
)


# Dependencies
SET(PRIVATE_LIBRARIES network_lib
                      network_type_mocks
                      GTest::gtest_main 
                      GTest::gmock_main
)


# Target
add_executable(PacketTests ${PACKET_TEST_SOURCES})

target_include_directories(PacketTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(PacketTests PRIVATE ${PRIVATE_LIBRARIES})


# Tests
gtest_discover_tests(PacketTests)