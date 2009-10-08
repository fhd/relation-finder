#ifndef GRAPH_HPP
#define GRAPH_HPP

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

#endif /* GRAPH_HPP */
