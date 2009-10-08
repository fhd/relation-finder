#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <deque>
#include <map>

/** Contains types for building and searching a graph */
namespace graph
{
	/** A node in a graph */
	typedef unsigned int node_t;

	/** A list of nodes */
	typedef std::deque<node_t> nodes_t;

	/** A path through a graph */
	typedef std::deque<node_t> path_t;

	/** An agenda for search algorithms */
	typedef std::deque<path_t> agenda_t;

	/** A graph **/
	typedef std::map<node_t, nodes_t> graph_t;
}

#endif /* GRAPH_HPP */
