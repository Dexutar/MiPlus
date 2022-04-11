# Sources
SET(SERVER_SOURCES  main.cpp)


# Dependencies
SET(PRIVATE_LIBRARIES network_lib
                      Threads::Threads
)


# Target
add_executable(server ${SERVER_SOURCES})

target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(server PRIVATE ${PRIVATE_LIBRARIES})