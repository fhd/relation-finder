#include <string>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE graph_searcher
#include <boost/test/unit_test.hpp>
#include <boost/foreach.hpp>

#include "../../src/wbd/graph_searcher.hpp"

// TODO: Write some more tests.

std::string path_to_string(graph::path_t &path)
{
	std::stringstream s;
	s << "[";
	BOOST_FOREACH (unsigned int node, path) {
			s << node;
			if (node != path.back())
				s << " -> ";
	}
	s << "]";
	return s.str();
}

void check_path(graph::path_t &expected_path, graph::path_t &path)
{
	BOOST_REQUIRE_EQUAL(expected_path.size(), path.size());

	for (unsigned int i = 0; i < expected_path.size(); i++)
		if (expected_path.at(i) != path.at(i))
			BOOST_ERROR("Incorrect path: Expected "
					<< path_to_string(expected_path)
					<< " but got " << path_to_string(path) << ".");
}

BOOST_AUTO_TEST_CASE(test_simple_path)
{
	// Setting up the fixture
	graph::graph_t graph;

	graph::nodes_t edge0, edge1, edge2, edge3, edge4, edge5, edge6,	edge7;
	edge1.push_back(2);
	edge1.push_back(3);
	edge2.push_back(1);
	edge2.push_back(4);
	edge3.push_back(1);
	edge3.push_back(6);
	edge4.push_back(2);
	edge4.push_back(5);
	edge4.push_back(6);
	edge5.push_back(4);
	edge6.push_back(3);
	edge6.push_back(4);
	edge6.push_back(7);
	edge7.push_back(6);
	graph[0] = edge0;
	graph[1] = edge1;
	graph[2] = edge2;
	graph[3] = edge3;
	graph[4] = edge4;
	graph[5] = edge5;
	graph[6] = edge6;
	graph[7] = edge7;

	// Expected result
	graph::path_t expected_path;
	expected_path.push_back(1);
	expected_path.push_back(3);
	expected_path.push_back(6);
	expected_path.push_back(7);

	// Calculate the way from 1 to 7
	graph_searcher *s = new graph_searcher(graph);
	graph::path_t *path = s->find_shortest_path(1, 7, 5);

	// Check the result
	BOOST_REQUIRE_MESSAGE(path, "No path was found.");

	check_path(expected_path, *path);
}

