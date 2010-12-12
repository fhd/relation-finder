#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE searcher

#include <string>
#include <boost/assign.hpp>
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include <searcher.hpp>

std::string path_to_string(Graph::Path_type& path)
{
    std::stringstream s;
    s << "[";
    BOOST_FOREACH (Graph::Node_type node, path) {
        s << node;
        if (node != path.back())
            s << " -> ";
    }
    s << "]";
    return s.str();
}

void check_path(Graph::Path_type& expected_path, Graph::Path_type &path)
{
    BOOST_REQUIRE_EQUAL(expected_path.size(), path.size());

    for (unsigned int i = 0; i < expected_path.size(); i++)
        if (expected_path.at(i) != path.at(i))
            BOOST_FAIL("Incorrect path: Expected "
                       << path_to_string(expected_path)
                       << " but got " << path_to_string(path) << ".");
}

struct Small_graph {
    Small_graph()
    {
        using namespace boost::assign;
        graph[1] = list_of(2)(3);
        graph[2] = list_of(1)(4);
        graph[3] = list_of(1)(6);
        graph[4] = list_of(2)(5)(6);
        graph[5] = list_of(4);
        graph[6] = list_of(3)(4)(7);
        graph[7] = list_of(6);
    }

    ~Small_graph() {}

    Graph::Graph_type graph;
};

struct Large_graph {
    Large_graph()
    {
        using namespace boost::assign;
        graph[1] = list_of(2)(3)(5)(6)(9);
        graph[2] = list_of(1)(4)(5)(10);
        graph[3] = list_of(1)(4)(7);
        graph[4] = list_of(2)(3)(5)(8)(10);
        graph[5] = list_of(1)(2)(4);
        graph[6] = list_of(1)(9);
        graph[7] = list_of(3)(8)(16);
        graph[8] = list_of(4)(7);
        graph[9] = list_of(1)(6)(11);
        graph[10] = list_of(2)(4)(13);
        graph[11] = list_of(9)(14);
        graph[12] = list_of(8)(14)(15);
        graph[13] = list_of(10);
        graph[14] = list_of(11)(12);
        graph[15] = list_of(12);
        graph[16] = list_of(7);
    }

    ~Large_graph() {}

    Graph::Graph_type graph;
};

BOOST_FIXTURE_TEST_CASE(test_simple_path, Small_graph)
{
    Searcher s(graph);
    Graph::Path_type path = s.find_shortest_path(1, 7, 5);
    BOOST_REQUIRE_MESSAGE(path.size() > 0, "No path was found.");

    using namespace boost::assign;
    Graph::Path_type expected_path = list_of(1)(3)(6)(7);
    check_path(expected_path, path);
}

BOOST_FIXTURE_TEST_CASE(test_impossible_path, Small_graph)
{
    Searcher s(graph);
    Graph::Path_type path = s.find_shortest_path(1, 1000, 5);
    BOOST_REQUIRE_MESSAGE(path.size() == 0,
                          "A path was found, although there can't be one.");
}

BOOST_FIXTURE_TEST_CASE(test_complex1, Large_graph)
{
    Searcher s(graph);
    Graph::Path_type path = s.find_shortest_path(15, 16, 5);

    using namespace boost::assign;
    Graph::Path_type expected_path = list_of(15)(12)(8)(7)(16);
    check_path(expected_path, path);
}

BOOST_FIXTURE_TEST_CASE(test_complex2, Large_graph)
{
    Searcher s(graph);
    Graph::Path_type path = s.find_shortest_path(1, 14, 5);

    using namespace boost::assign;
    Graph::Path_type expected_path = list_of(1)(9)(11)(14);
    check_path(expected_path, path);
}

BOOST_FIXTURE_TEST_CASE(test_complex3, Large_graph)
{
    Searcher s(graph);
    Graph::Path_type path = s.find_shortest_path(13, 5, 5);

    using namespace boost::assign;
    Graph::Path_type expected_path = list_of(13)(10)(2)(5);
    check_path(expected_path, path);
}

BOOST_FIXTURE_TEST_CASE(test_complex4, Large_graph)
{
    Searcher s(graph);
    Graph::Path_type path = s.find_shortest_path(2, 14, 5);

    using namespace boost::assign;
    // 2 -> 4 -> 8 -> 12 -> 14 would be correct as well
    Graph::Path_type expected_path = list_of(2)(1)(9)(11)(14);
    check_path(expected_path, path);
}
