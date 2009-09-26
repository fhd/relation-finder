#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <map>
#include <deque>

/** Contains types for building and searching a graph */
namespace graph
{
	/** A node in a graph */
	typedef unsigned int node_t;

	/** Multiple nodes */
	typedef std::deque <node_t> nodes_t;

	/** A path through a graph */
	typedef std::deque <node_t> path_t;

	/** A graph **/
	typedef std::map <node_t, nodes_t> graph_t;

	/** An agenda for a search algorithm */
	typedef std::deque <path_t> agenda_t;
}

/** Searches a graph. */
class graph_searcher
{
public:
	/** Constructor that sets the graph to the given value */
	graph_searcher(const graph::graph_t &graph);

	/** Destructor */
	~graph_searcher();

	/**
	 * Returns the shortest path from start to goal.
	 * Stops once the depth limit is reached.
	 * Returns NULL if no path could be found.
	 */
	graph::path_t *find_shortest_path(graph::node_t start, graph::node_t goal, int depth_limit);

private:
	graph::graph_t m_graph;

	/**
	 * Performs a depth-limited breadth-first search to find the shortest path
	 * between two nodes. Returns NULL if no path could be found.
	 * Uses a memoisation table to never expand the same node twice.
	 * Stops once the depth limit is reached, .
	 */
	graph::path_t *breadth_first(graph::agenda_t &agenda, graph::nodes_t &memtable, graph::node_t goal,	int depth_limit);

	/**
	 * Finds all the successors of the current node.
	 * Th all siblings we didn't process yet and
	 * updates the memoisation table
	 */
	graph::nodes_t find_successors(graph::node_t node, graph::nodes_t &memtable);
};

#endif /* SEARCH_HPP */
