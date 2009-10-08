#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <boost/shared_ptr.hpp>
#include "graph.hpp"

/** Searches a graph. */
class searcher
{
public:
	/** Constructor that sets the graph to the given value */
	searcher(graph::graph_t &graph);

	/**
	 * Returns the shortest path from start to goal.
	 * Stops once the depth limit is reached.
	 * Returns NULL if no path could be found.
	 */
	boost::shared_ptr<graph::path_t> find_shortest_path(graph::node_t start,
			graph::node_t goal, unsigned int depth_limit);

private:
	graph::graph_t graph_;

	/**
	 * Performs a depth-limited breadth-first search to find the shortest
	 * path between two nodes. Returns NULL if no path could be found.
	 * Uses a memoisation table to never expand the same node twice.
	 * Stops once the depth limit is reached, .
	 */
	boost::shared_ptr<graph::path_t> find_breadth_first(
			graph::agenda_t &agenda, graph::nodes_t &memtable,
			graph::node_t goal, unsigned int depth_limit);

	/**
	 * Finds all the successors of the current node.
	 * Th all siblings we didn't process yet and
	 * updates the memoisation table
	 */
	graph::nodes_t find_successors(graph::node_t node,
			graph::nodes_t &memtable);
};

#endif /* SEARCH_HPP */