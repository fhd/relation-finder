#include <iostream>
#include <boost/thread.hpp>
#include <boost/thread/xtime.hpp>
#include <asio.hpp>
#include "options.hpp"
#include "util.hpp"
#include "fetcher.hpp"
#include "tcp_server.hpp"

/** A thread functor, updating the relations */
struct fetcher_thread
{
	fetcher_thread(const unsigned int &fetch_interval)
	{
		fetch_interval_ = fetch_interval;
	}

	void operator()()
	{
		boost::shared_ptr<fetcher> f = fetcher::instance();
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
};

int main(int argc, char **argv)
{
	try {
		// Parse the commandline options
		boost::shared_ptr<options> opts = options::instance();
		try {
			opts->parse(argc, argv);
		} catch (int e) {
			return e;
		}

		util::message("Initialised.");

		// Start the fetcher thread
		fetcher_thread fetcher(opts->fetching_interval());
		boost::thread thread(fetcher);

		// Start the server and listen for incoming connections
		asio::io_service io_service;
		tcp_server server(io_service, opts->port());
		io_service.run();
	} catch (std::exception &e) {
		std::cerr << "Caught an exception: " << e.what() << std::endl;
	}

	return 0;
}
