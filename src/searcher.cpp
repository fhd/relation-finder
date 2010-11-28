#include <boost/foreach.hpp>
#include "searcher.hpp"

Searcher::Searcher(const Graph::graph_t& graph) : graph(graph)
{
}

boost::shared_ptr<Graph::path_t> Searcher::find_shortest_path(
        const Graph::node_t& start, const Graph::node_t& goal,
        unsigned int depth_limit) const
{
    Graph::agenda_t agenda;
    Graph::nodes_t memtable;
    Graph::path_t first;
    first.push_back(start);
    agenda.push_back(first);
    return find_breadth_first(agenda, memtable, goal, depth_limit);
}

boost::shared_ptr<Graph::path_t> Searcher::find_breadth_first(
        Graph::agenda_t& agenda, Graph::nodes_t& memtable,
        const Graph::node_t& goal, unsigned int depth_limit) const
{
    // A dead end was reached
    if (agenda.size() == 0)
        return boost::shared_ptr<Graph::path_t>();

    Graph::path_t current_path = agenda.front();

    // The depth limit was reached
    if (current_path.size() > depth_limit)
        return boost::shared_ptr<Graph::path_t>();

    Graph::node_t current_node = current_path.back();
    agenda.pop_front();

    // The currently expanded node is the goal
    if (current_node == goal)
        return boost::shared_ptr<Graph::path_t>(
                new Graph::path_t(current_path));

    // Add the successors to the end of the agenda (breadth-first)
    Graph::nodes_t successors = find_successors(current_node, memtable);
    BOOST_FOREACH (Graph::node_t snode, successors) {
        Graph::path_t path(current_path);
        path.push_back(snode);
        // Use push_front instead to perform a depth-first search
        agenda.push_back(path);
    }

    // Search again
    return find_breadth_first(agenda, memtable, goal, depth_limit);
}

Graph::nodes_t Searcher::find_successors(const Graph::node_t& current,
                                         Graph::nodes_t& memtable) const
{
    Graph::nodes_t successors;
    Graph::graph_t::const_iterator iter = graph.find(current);
    // This node has no siblings at all
    if (iter == graph.end())
        return successors;

    // Find all successors that are not yet on the memoisation table
    Graph::nodes_t siblings = iter->second;
    BOOST_FOREACH (Graph::node_t sibling, siblings) {
        Graph::nodes_t::iterator miter = find(memtable.begin(),
                                              memtable.end(), sibling);
        if (miter == memtable.end()) {
            memtable.push_back(sibling);
            successors.push_back(sibling);
        }
    }
    return successors;
}
