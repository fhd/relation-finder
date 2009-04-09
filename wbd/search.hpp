#ifndef _SEARCH_HPP
#define _SEARCH_HPP

#include "typedef.h"

class search
{
public:
	search(const graph_t &graph);
	~search();
	path_t *shortest_path(node_t start, node_t goal, int depth_limit);

private:
	graph_t m_graph;

	nodes_t find_successors(node_t node, nodes_t &memtable);
	path_t *breadth_first(agenda_t &agenda, nodes_t &memtable, node_t goal, int depth_limit);
};

#endif /* _SEARCH_HPP */
