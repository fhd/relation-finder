#ifndef FETCHER_HPP
#define FETCHER_HPP

#include <boost/thread/mutex.hpp>
#include "searcher.hpp"

/** Reads relations regularly from the database */
class fetcher
{
public:
	/** Singleton instance getter */
	static fetcher *get_instance();

	/** Returns the last read relations */
	graph::graph_t get_relations();

	/** Fetches new relations from the database regularly */
	void fetch();

private:
	// TODO: Use a shared pointer for the instance?
	static fetcher *instance_;
	graph::graph_t relations_;
	boost::mutex relations_mutex_;

	fetcher();
};

#endif /* FETCHER_HPP */
