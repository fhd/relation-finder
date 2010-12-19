set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")

find_package(Boost COMPONENTS system filesystem program_options thread REQUIRED)
find_package(PQXX REQUIRED)

add_executable(
  relation-finder
  fetcher.cpp
  logger.cpp
  main.cpp
  options.cpp
  searcher.cpp
  tcp_connection.cpp
  tcp_server.cpp
  util.cpp)

target_link_libraries(
  relation-finder
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  ${PQXX_LIBRARIES})

install(TARGETS relation-finder DESTINATION bin)