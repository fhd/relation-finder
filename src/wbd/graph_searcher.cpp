#include <cassert>
#include <algorithm>
#include <iostream>
#include <boost/foreach.hpp>

#include "graph_searcher.hpp"

graph_searcher::graph_searcher(graph::graph_t &graph)
: m_graph(graph)
{
}

graph_searcher::~graph_searcher()
{
}

graph::path_t *graph_searcher::find_shortest_path(graph::node_t start,
	graph::node_t goal, int depth_limit)
{
	graph::agenda_t agenda;
	graph::nodes_t memtable;
	graph::path_t first;
	first.push_back(start);
	agenda.push_back(first);
	return find_breadth_first(agenda, memtable, goal, depth_limit);
}

graph::path_t *graph_searcher::find_breadth_first(graph::agenda_t &agenda,
	graph::nodes_t &memtable, graph::node_t goal, int depth_limit)
{
#if 0
	std::cout << "breath_first:" << std::endl;
	std::cout << "  agenda:";
	BOOST_FOREACH (path_t path, agenda) {
		std::cout << " " << path.back();
	}
	std::cout << std::endl;
	std::cout << "  memtable:";
	BOOST_FOREACH (node_t node, memtable) {
		std::cout << " " << node;
	}
	std::cout << std::endl;
	std::cout << "  goal: " << goal << std::endl;
	std::cout << "  depth_limit: " << depth_limit << std::endl;
	std::cout << "---------------" << std::endl;
#endif

	// A dead end was reached
	if (agenda.size() == 0)
		return NULL;

	graph::path_t current_path = agenda.front();

	// The depth limit was reached
	if (current_path.size() > depth_limit)
		return NULL;

	graph::node_t current_node = current_path.back();
	agenda.pop_front();

	// The currently expanded node is the goal
	if (current_node == goal)
		return new graph::path_t(current_path);

	// Add the successors to the end of the agenda (breadth-first)
	graph::nodes_t successors = find_successors(current_node, memtable);
	BOOST_FOREACH (graph::node_t snode, successors) {
		graph::path_t path(current_path);
		path.push_back(snode);
		// Use push_front instead to perform a depth-first search
		agenda.push_back(path);
	}

	// Search again
	return find_breadth_first(agenda, memtable, goal, depth_limit);
}

graph::nodes_t graph_searcher::find_successors(graph::node_t current,
	graph::nodes_t &memtable)
{
	graph::nodes_t successors;
	graph::graph_t::iterator iter = m_graph.find(current);
	// This node has no siblings at all
	if (iter == m_graph.end())
		return successors;

	// Find all successors that are not yet on the memoisation table
	graph::nodes_t siblings = iter->second;
	BOOST_FOREACH (graph::node_t sibling, siblings) {
		graph::nodes_t::iterator miter =
			find(memtable.begin(), memtable.end(), sibling);
		if (miter == memtable.end()) {
			memtable.push_back(sibling);
			successors.push_back(sibling);
		}
	}
#if 0
	std::cout << "successors of " << current << ":";
	BOOST_FOREACH (node_t node, successors) {
		std::cout << " " << node;
	}
	std::cout << std::endl;
#endif
	return successors;
}
