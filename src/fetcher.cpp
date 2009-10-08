#include "fetcher.hpp"

fetcher *fetcher::instance_ = NULL;

fetcher *fetcher::get_instance()
{
	// TODO: Make thread-safe
	if (!instance_)
		instance_ = new fetcher();
	return instance_;
}

graph::graph_t fetcher::get_relations()
{
	boost::mutex::scoped_lock lock(relations_mutex_);
	return relations_;
}

void fetcher::fetch()
{
	// TODO: Actually fetch the relations from the database in a loop
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
	relations_[0] = edge0;
	relations_[1] = edge1;
	relations_[2] = edge2;
	relations_[3] = edge3;
	relations_[4] = edge4;
	relations_[5] = edge5;
	relations_[6] = edge6;
	relations_[7] = edge7;
}

fetcher::fetcher()
{
}
