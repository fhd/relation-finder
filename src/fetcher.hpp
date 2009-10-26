#ifndef FETCHER_HPP
#define FETCHER_HPP

#include <string>
#include <sstream>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include "graph.hpp"

/** Reads relations regularly from the database */
class fetcher
{
public:
	/** Singleton instance getter */
	static boost::shared_ptr<fetcher> instance();

	/** Returns the last read relations */
	graph::graph_t relations() const;

	/** Fetches new relations from the database regularly */
	void fetch();

private:
	static boost::shared_ptr<fetcher> instance_;
	static boost::mutex instance_mutex_;
	graph::graph_t relations_;
	mutable boost::mutex relations_mutex_;
	bool verbose_;
	
	fetcher();

	class connect_string_builder
	{
	public:
		void set_option(const std::string &name, const std::string &value);
		std::string string() const;

	private:
		std::stringstream stream_;
	};
};

#endif /* FETCHER_HPP */
