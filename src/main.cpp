#include <iostream>
#include <boost/thread.hpp>
#include <boost/thread/xtime.hpp>
#include <asio.hpp>
#include "options.hpp"
#include "fetcher.hpp"
#include "tcp_server.hpp"

/** A thread functor, updating the relations */
struct fetcher_thread
{
	fetcher_thread(unsigned int fetch_interval, bool verbose)
	: fetch_interval_(fetch_interval)
	, verbose_(verbose)
	{
	}

	void operator()()
	{
		boost::shared_ptr<fetcher> f = fetcher::instance();
		f->set_verbose(verbose_);
		for (;;) {
			// Fetch new relations
			f->fetch();

			// Sleep for a while
			boost::xtime xt;
			boost::xtime_get(&xt, boost::TIME_UTC);
			xt.sec += fetch_interval_;
			boost::thread::sleep(xt);
		}
	}

	unsigned int fetch_interval_;
	bool verbose_;
};

int main(int argc, char **argv)
{
	try {
		// Parse the commandline options
		boost::shared_ptr<options> o = options::instance();
		try {
			o->parse(argc, argv);
		} catch (int e) {
			return e;
		}

		// Start the fetcher thread
		fetcher_thread fetcher(o->fetching_interval(), o->verbose());
		boost::thread thread(fetcher);

		// Start the server and listen for incoming connections
		asio::io_service io_service;
		tcp_server server(io_service, o->port(), o->depth_limit());
		io_service.run();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
