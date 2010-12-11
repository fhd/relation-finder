set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")

find_package(Boost COMPONENTS system REQUIRED)

add_executable(relation-finder-client "relation_finder_client.cpp")

target_link_libraries(relation-finder-client ${Boost_SYSTEM_LIBRARY})

install(TARGETS relation-finder-client DESTINATION bin)