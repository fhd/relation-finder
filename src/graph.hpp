#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <deque>
#include <map>

/// Contains types for building and searching a graph
namespace Graph {
    /// A node in a graph
    typedef unsigned int Node_type;

    /// A list of nodes
    typedef std::deque<Node_type> Nodes_type;

    /// A path through a graph
    typedef std::deque<Node_type> Path_type;

    /// An agenda for search algorithms
    typedef std::deque<Path_type> Agenda_type;

    /// A graph
    typedef std::map<Node_type, Nodes_type> Graph_type;
}

#endif
