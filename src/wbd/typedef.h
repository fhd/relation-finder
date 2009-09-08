#ifndef _TYPEDEF_H
#define _TYPEDEF_H

#include <map>
#include <deque>

typedef unsigned int node_t;
typedef std::deque<node_t> nodes_t;
typedef std::deque<node_t> path_t;
typedef std::map<node_t, nodes_t> graph_t;
typedef std::deque<path_t> agenda_t;

#endif
