set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

include_directories(${SRC_DIR})
find_package(Boost COMPONENTS system unit_test_framework REQUIRED)

add_executable(searcher_test searcher_test.cpp ${SRC_DIR}/searcher.cpp)
target_link_libraries(searcher_test ${Boost_LIBRARIES})
add_test(searcher ${EXECUTABLE_OUTPUT_PATH}/searcher_test)

add_executable(util_test util_test.cpp ${SRC_DIR}/util.cpp)
target_link_libraries(util_test ${Boost_LIBRARIES})
add_test(util ${EXECUTABLE_OUTPUT_PATH}/util_test)
