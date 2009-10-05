#include "fetcher.hpp"

fetcher *fetcher::m_instance = NULL;

fetcher *fetcher::get_instance()
{
	// TODO: Make this thread-safe
	if (m_instance == NULL)
		m_instance = new fetcher();
	return m_instance;
}

graph::graph_t fetcher::get_relations()
{
	// TODO: Make this thread-safe
	return m_relations;
}

fetcher::fetcher()
{
}

fetcher::~fetcher()
{
}

void fetcher::run()
{
	// TODO: Actually fetch the relations from the database
	graph::nodes_t edge0, edge1, edge2, edge3, edge4, edge5, edge6,	edge7;
	edge1.push_back(2);
	edge1.push_back(3);
	edge2.push_back(1);
	edge2.push_back(4);
	edge3.push_back(1);
	edge3.push_back(6);
	edge4.push_back(2);
	edge4.push_back(5);
	edge4.push_back(6);
	edge5.push_back(4);
	edge6.push_back(3);
	edge6.push_back(4);
	edge6.push_back(7);
	edge7.push_back(6);
	m_relations[0] = edge0;
	m_relations[1] = edge1;
	m_relations[2] = edge2;
	m_relations[3] = edge3;
	m_relations[4] = edge4;
	m_relations[5] = edge5;
	m_relations[6] = edge6;
	m_relations[7] = edge7;
}
