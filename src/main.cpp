#include <iostream>
#include <boost/program_options.hpp>
#include <boost/thread.hpp>
#include <boost/thread/xtime.hpp>
#include <asio.hpp>
#include "fetcher.hpp"
#include "tcp_server.hpp"

#define VERSION "0.1"
#define DESCRIPTION_TEXT \
		"A daemon calculating the shortest path between two people " \
		"in a social network."
#define USAGE_TEXT "Usage: wbd [OPTION]..."
#define VERSION_TEXT \
		"wbd (Wanjas Beziehungs Daemon) "VERSION"\n"\
		"Copyright (C) 2009 Felix H. Dahlke.\n"\
		"Licensed under the MIT License."

#define DEFAULT_PORT 8888
#define DEFAULT_FETCHING_INTERVAL 300
#define DEFAULT_DEPTH_LIMIT 5

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
		boost::shared_ptr<fetcher> f = fetcher::get_instance();
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

/** Parses commandline options, returns true if the program should continue. */
bool parse_options(int argc, char *argv[],
		unsigned int &port,
		unsigned int &fetching_interval,
		unsigned int &depth_limit,
		bool &verbose)
{
	namespace po = boost::program_options;
	po::options_description options("Options");
	options.add_options()
		("port", po::value<unsigned int>(&port)->default_value(DEFAULT_PORT),
				"set the tcp port")
		("fetching-interval",
		 		po::value<unsigned int>(&fetching_interval)->default_value(
					DEFAULT_FETCHING_INTERVAL),
				"set the time (in seconds) to wait before fetching new relations from the database")
		("depth-limit",
		 		po::value<unsigned int>(&depth_limit)->default_value(
					DEFAULT_DEPTH_LIMIT),
				"set the maximum length of relationship paths")
		("verbose", "explain what is happening")
		("help", "display this help and exit")
		("version",	"output version information and exit");

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, options), vm);
	po::notify(vm);

	if (vm.count("help")) {
		std::cout << USAGE_TEXT << std::endl
				<< DESCRIPTION_TEXT << std::endl << std::endl
				<< options << std::endl;
		return false; 
	}

	if (vm.count("version")) {
		std::cout << VERSION_TEXT << std::endl;
		return false;
	}

	verbose = vm.count("verbose");

	return true;
}

int main(int argc, char *argv[])
{
	try {
		// Parse the commandline options
		unsigned int port, fetching_interval = 5, depth_limit;
		bool verbose;
		if (!parse_options(argc, argv, port, fetching_interval, depth_limit,
					verbose))
			return 0;

		// Start the fetcher
		fetcher_thread fetcher(fetching_interval, verbose);
		boost::thread thread(fetcher);

		// Start the server and listen for incoming connections
		asio::io_service io_service;
		tcp_server server(io_service, port, depth_limit);
		io_service.run();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
