#include <boost/assign.hpp>
#include "fetcher.hpp"

boost::shared_ptr<fetcher> fetcher::instance_ = boost::shared_ptr<fetcher>();
boost::mutex fetcher::instance_mutex_;

boost::shared_ptr<fetcher> fetcher::get_instance()
{
	boost::mutex::scoped_lock lock(instance_mutex_);
	if (!instance_)
		instance_ = boost::shared_ptr<fetcher>(new fetcher());
	return instance_;
}

graph::graph_t fetcher::get_relations()
{
	boost::mutex::scoped_lock lock(relations_mutex_);
	return relations_;
}

void fetcher::fetch()
{
	boost::mutex::scoped_lock lock(relations_mutex_);
	relations_.clear();

	// TODO: Actually fetch the relations from the database
	using namespace boost::assign;
	relations_[1] = list_of(2)(3);
	relations_[2] = list_of(1)(4);
	relations_[3] = list_of(1)(6);
	relations_[4] = list_of(2)(5)(6);
	relations_[5] = list_of(4);
	relations_[6] = list_of(3)(4)(7);
	relations_[7] = list_of(6);
}

fetcher::fetcher()
{
}
