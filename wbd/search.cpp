#include <cassert>
#include <algorithm>
#include <iostream>
#include <boost/foreach.hpp>
#include "search.hpp"

/**
 * Constructor that sets the graph to the given value
 */
search::search(const graph_t &graph)
: m_graph(graph)
{
}

/**
 * Deconstructor
 */
search::~search()
{
}

/**
 * Returns the shortest path from start to goal.
 * Stops once the depth limit is reached.
 * Returns NULL if no path could be found.
 */
path_t *search::shortest_path(node_t start, node_t goal, int depth_limit)
{
	agenda_t agenda;
	nodes_t memtable;
	path_t first;
	first.push_back(start);
	agenda.push_back(first);
	return breadth_first(agenda, memtable, goal, depth_limit);
}

/**
 * Performs a depth-limited breadth-first search to find the shortest path
 * between two nodes. Returns NULL if no path could be found.
 * Uses a memoisation table to never expand the same node twice.
 * Stops once the depth limit is reached, .
 */
path_t *search::breadth_first(agenda_t &agenda, nodes_t &memtable, node_t goal, int depth_limit)
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
	if (agenda.size() == 0) {
		return NULL;
	}

	path_t current_path = agenda.front();

	// The depth limit was reached
	if (current_path.size() > depth_limit) {
		return NULL;
	}

	node_t current_node = current_path.back();
	agenda.pop_front();

	// The currently expanded node is the goal
	if (current_node == goal) {
		return new path_t(current_path);
	}

	// Add the successors to the end of the agenda (breadth-first)
	nodes_t successors = find_successors(current_node, memtable);
	BOOST_FOREACH (node_t snode, successors) {
		path_t path(current_path);
		path.push_back(snode);
		// Use push_front instead to perform a depth-first search
		agenda.push_back(path);
	}

	// Search again
	return breadth_first(agenda, memtable, goal, depth_limit);
}

/**
 * Finds all the successors of the current node,
 * i.e. all siblings we didn't process yet and
 * updates the memoisation table
 */
nodes_t search::find_successors(node_t current, nodes_t &memtable)
{
	nodes_t successors;
	graph_t::iterator iter = m_graph.find(current);
	// This node has no siblings at all
	if (iter == m_graph.end()) {
		return successors;
	}

	// Find all successors that are not yet on the memoisation table
	nodes_t siblings = iter->second;
	BOOST_FOREACH (node_t sibling, siblings) {
		nodes_t::iterator miter =
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
