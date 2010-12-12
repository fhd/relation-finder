set(RELATION_FINDER_SRC_DIR ../src)

include_directories(${RELATION_FINDER_SRC_DIR})
find_package(Boost COMPONENTS system unit_test_framework REQUIRED)
add_library(searcher ${RELATION_FINDER_SRC_DIR}/searcher.cpp)

add_executable(searcher_test searcher_test.cpp)
target_link_libraries(searcher_test ${Boost_LIBRARIES} searcher)
add_test(searcher ${EXECUTABLE_OUTPUT_PATH}/searcher_test)

add_executable(util_test util_test.cpp)
target_link_libraries(util_test ${Boost_LIBRARIES} util)
add_test(util ${EXECUTABLE_OUTPUT_PATH}/util_test)
