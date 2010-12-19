#ifndef SEARCHER_HPP
#define SEARCHER_HPP

#include "graph.hpp"

/// Searches a graph
class Searcher {
public:
    /// Constructor that sets the graph to the given value
    Searcher(const Graph::Graph_type& graph);

    /**
     * Returns the shortest path from start to goal.
     * Stops once the depth limit is reached.
     * Returns an empty path if no path could be found.
     */
    Graph::Path_type find_shortest_path(const Graph::Node_type& start,
                                        const Graph::Node_type& goal,
                                        unsigned int depth_limit) const;

private:
    const Graph::Graph_type& graph;

    /**
     * Performs a depth-limited breadth-first search to find the shortest
     * path between two nodes. Returns an empty path if no path could be found.
     * Uses a memoisation table to never expand the same node twice.
     * Stops once the depth limit is reached.
     */
    Graph::Path_type find_breadth_first(Graph::Agenda_type& agenda,
                                        Graph::Nodes_type& memtable,
                                        const Graph::Node_type& goal,
                                        unsigned int depth_limit) const;

    /**
     * Finds all the successors of the current node.
     * Ignores those already on the memoisation table and updates the table.
     */
    Graph::Nodes_type find_successors(const Graph::Node_type& node,
                                      Graph::Nodes_type& memtable) const;
};

#endif
