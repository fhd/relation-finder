#include <iostream>
#include <boost/thread.hpp>
#include <boost/thread/xtime.hpp>
#include <asio.hpp>
#include "fetcher.hpp"
#include "tcp_server.hpp"

/** A thread functor updating the relations */
struct fetcher_thread
{
	fetcher_thread(unsigned int fetch_interval)
	: fetch_interval_(fetch_interval)
	{
	}

	void operator()()
	{
		for (;;) {
			// Fetch new relations
			fetcher::get_instance()->fetch();

			// Sleep for a while
			boost::xtime xt;
			boost::xtime_get(&xt, boost::TIME_UTC);
			xt.sec += fetch_interval_;
			boost::thread::sleep(xt);
		}
	}

	unsigned int fetch_interval_;
};

int main(int argc, char **argv)
{
	/*
	 * TODO: Read the following from cmd options:
	 * - the server's port
	 * - the searcher's depth limit
	 * - the fetcher's fetching interval
	 *
	 * TODO: Handle signals properly
	 */

	// start the fetcher
	boost::thread thread(fetcher_thread(300));

	// start the server to listen for incoming connections
	try {
		asio::io_service io_service;
		tcp_server server(io_service, 8888);
		io_service.run();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
