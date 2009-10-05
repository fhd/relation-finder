#ifndef FETCHER_HPP
#define FETCHER_HPP

#include "thread.hpp"
#include "searcher.hpp"

/** Reads relations regularly from the database */
class fetcher : public thread
{
public:
	/** Singleton instance getter */
	static fetcher *get_instance();

	/** Returns the last read relations */
	graph::graph_t get_relations();

private:
	static fetcher *m_instance;
	graph::graph_t m_relations;

	/** Constructor */
	fetcher();

	/** Destructor */
	~fetcher();

	void run();
};

#endif /* FETCHER_HPP */
