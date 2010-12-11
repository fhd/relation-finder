set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")

find_package(Boost COMPONENTS system filesystem program_options thread REQUIRED)
find_package(PQXX REQUIRED)

file(GLOB SOURCES "*.cpp")
add_executable(relation-finder ${SOURCES})

target_link_libraries(
  relation-finder
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  ${PQXX_LIBRARIES})

install(TARGETS relation-finder DESTINATION bin)