#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include "searcher.hpp"

Searcher::Searcher(const Graph::Graph_type& graph) : graph(graph)
{
}

Graph::Path_type Searcher::find_shortest_path(const Graph::Node_type& start,
                                              const Graph::Node_type& goal,
                                              unsigned int depth_limit) const
{
    Graph::Agenda_type agenda;
    Graph::Nodes_type memtable;
    Graph::Path_type first;
    first.push_back(start);
    agenda.push_back(first);
    return find_breadth_first(agenda, memtable, goal, depth_limit);
}

Graph::Path_type Searcher::find_breadth_first(Graph::Agenda_type& agenda,
                                              Graph::Nodes_type& memtable,
                                              const Graph::Node_type& goal,
                                              unsigned int depth_limit) const
{
    // A dead end was reached
    if (agenda.size() == 0)
        return Graph::Path_type();

    Graph::Path_type current_path = agenda.front();

    // The depth limit was reached
    if (current_path.size() > depth_limit)
        return Graph::Path_type();

    Graph::Node_type current_node = current_path.back();
    agenda.pop_front();

    // The currently expanded node is the goal
    if (current_node == goal)
        return current_path;

    // Add the successors to the end of the agenda (breadth-first)
    Graph::Nodes_type successors = find_successors(current_node, memtable);
    BOOST_FOREACH (Graph::Node_type snode, successors) {
        Graph::Path_type path(current_path);
        path.push_back(snode);
        // Use push_front instead to perform a depth-first search
        agenda.push_back(path);
    }

    // Search again
    return find_breadth_first(agenda, memtable, goal, depth_limit);
}

Graph::Nodes_type Searcher::find_successors(const Graph::Node_type& current,
                                            Graph::Nodes_type& memtable) const
{
    Graph::Nodes_type successors;
    Graph::Graph_type::const_iterator iter = graph.find(current);
    // This node has no siblings at all
    if (iter == graph.end())
        return successors;

    // Find all successors that are not yet on the memoisation table
    Graph::Nodes_type siblings = iter->second;
    BOOST_FOREACH (Graph::Node_type sibling, siblings) {
        Graph::Nodes_type::iterator miter = find(memtable.begin(),
                                                 memtable.end(), sibling);
        if (miter == memtable.end()) {
            memtable.push_back(sibling);
            successors.push_back(sibling);
        }
    }
    return successors;
}
