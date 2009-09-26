#include <iostream>
#include <boost/foreach.hpp>
#include "graph_searcher.hpp"

int main(int argc, char **argv)
{
	// TODO: Instead of this simple test, create a daemon.

	graph::graph_t graph;
/*
	nodes_t edge0, edge1, edge2, edge3;
	edge0.push_back(1);
	edge1.push_back(0);
	edge1.push_back(2);
	edge2.push_back(1);
	edge2.push_back(3);
	edge3.push_back(2);
	graph[0] = edge0;
	graph[1] = edge1;
	graph[2] = edge2;
	graph[3] = edge3;
*/
	graph::nodes_t edge0, edge1, edge2, edge3, edge4, edge5, edge6, edge7;
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

	// Den Weg von 1 nach 7 berechnen
	int start = 1;
	int goal = 7;
	int depth = 5;

	graph_searcher *s = new graph_searcher(graph);
	graph::path_t *path = s->find_shortest_path(start, goal, depth);
	if (!path) {
		std::cout << "Could not find shortest path." << std::endl;
	} else {
		std::cout << "The shortest path is: ";
		BOOST_FOREACH (graph::node_t node, *path) {
			std::cout << node;
			if (node != path->back()) {
				std::cout << " -> ";
			}
		}
		std::cout << std::endl;
	}

	delete s;
	delete path;

	return 0;
}
