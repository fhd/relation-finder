#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <boost/shared_ptr.hpp>
#include "graph.hpp"

/// Searches a graph
class Searcher {
public:
    /// Constructor that sets the graph to the given value
    Searcher(const Graph::graph_t& graph);

    /**
     * Returns the shortest path from start to goal.
     * Stops once the depth limit is reached.
     * Returns NULL if no path could be found.
     */
    boost::shared_ptr<Graph::path_t> find_shortest_path(
            const Graph::node_t& start, const Graph::node_t& goal,
            unsigned int depth_limit) const;

private:
    const Graph::graph_t& graph;

    /**
     * Performs a depth-limited breadth-first search to find the shortest
     * path between two nodes. Returns NULL if no path could be found.
     * Uses a memoisation table to never expand the same node twice.
     * Stops once the depth limit is reached.
     */
    boost::shared_ptr<Graph::path_t> find_breadth_first(
            Graph::agenda_t& agenda, Graph::nodes_t& memtable,
            const Graph::node_t& goal, unsigned int depth_limit) const;

    /**
     * Finds all the successors of the current node.
     * Ignores those already on the memoisation table and updates the table.
     */
    Graph::nodes_t find_successors(const Graph::node_t& node,
                                   Graph::nodes_t& memtable) const;
};

#endif
