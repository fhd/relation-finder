#include <iostream>
#include <fstream>
#include <vector>
#include <boost/program_options.hpp>
#include <boost/foreach.hpp>

#include "options.hpp"

#define VERSION "0.1"
#define DESCRIPTION_TEXT \
		"A daemon calculating the shortest path between two people " \
		"in a social network."
#define USAGE_TEXT "Usage: wbd [OPTION]..."
#define VERSION_TEXT \
		"wbd (Wanjas Beziehungs Daemon) "VERSION"\n"\
		"Copyright (C) 2009 Felix H. Dahlke.\n"\
		"Licensed under the MIT License."

#define CONFIG_FILE "wbd.cfg"
#define DEFAULT_PORT 8888
#define DEFAULT_FETCHING_INTERVAL 300
#define DEFAULT_DEPTH_LIMIT 5

namespace fs = boost::filesystem;
namespace po = boost::program_options;

boost::shared_ptr<options> options::instance_ = boost::shared_ptr<options>();
boost::mutex options::instance_mutex_;

boost::shared_ptr<options> options::get_instance()
{
	boost::mutex::scoped_lock lock(instance_mutex_);
	if (!instance_)
		instance_ = boost::shared_ptr<options>(new options());
	return instance_;
}

void options::parse(int argc, char **argv)
{
	boost::mutex::scoped_lock lock(options_mutex_);

	po::options_description desc("Options");
	desc.add_options()
		(
			"port",
			po::value<unsigned int>(&port_)->default_value(DEFAULT_PORT),
			"set the tcp port"
		)
		(
			"fetching-interval",
			po::value<unsigned int>(&fetching_interval_)->default_value(
					DEFAULT_FETCHING_INTERVAL),
			"set the time (in seconds) to wait before fetching new relations \
from the database"
		)
		(
			"depth-limit",
			po::value<unsigned int>(&depth_limit_)->default_value(
					DEFAULT_DEPTH_LIMIT),
			"set the maximum length of relationship paths"
		)
		("verbose", "explain what is happening")
		("help", "display this help and exit")
		("version",	"output version information and exit")
	;

	po::variables_map vm;

	// Read options from the command line
	po::store(po::parse_command_line(argc, argv, desc), vm);

	// Read options from the configuration file
	boost::shared_ptr<fs::path> config_file = find_config_file(argv[0]);
	if (config_file != NULL) {
		std::ifstream ifs(config_file->string().c_str());
		po::store(po::parse_config_file(ifs, desc), vm);
	}

	po::notify(vm);

	if (vm.count("help")) {
		std::cout << USAGE_TEXT << std::endl
				<< DESCRIPTION_TEXT << std::endl << std::endl
				<< desc << std::endl;
		throw 0;
	}

	if (vm.count("version")) {
		std::cout << VERSION_TEXT << std::endl;
		throw 0;
	}

	verbose_ = vm.count("verbose");
}

unsigned int options::get_port()
{
	boost::mutex::scoped_lock lock(options_mutex_);
	return port_;
}

unsigned int options::get_fetching_interval()
{
	boost::mutex::scoped_lock lock(options_mutex_);
	return fetching_interval_;
}

unsigned int options::get_depth_limit()
{
	boost::mutex::scoped_lock lock(options_mutex_);
	return depth_limit_;
}

bool options::get_verbose()
{
	boost::mutex::scoped_lock lock(options_mutex_);
	return verbose_;
}

options::options()
{
}

boost::shared_ptr<fs::path> options::find_config_file(char *binary_path)
{
	// Find the path to the binary's directory
	fs::path bin_path(binary_path);
	std::string bin_dir = bin_path.branch_path().string();

	// The following candidates will be searched in that order
	std::vector<fs::path> candidates;
	candidates.push_back(fs::path("etc/"CONFIG_FILE));
	candidates.push_back(fs::path(bin_dir + "/../etc/"CONFIG_FILE));
	candidates.push_back(fs::path("/etc/"CONFIG_FILE));

	// Check each of the candidates and return the first one that is found
	BOOST_FOREACH(fs::path candidate, candidates) {
		std::cout << candidate.string() << std::endl;
		if (fs::exists(candidate))
			return boost::shared_ptr<fs::path>(new fs::path(candidate));
	}

	return boost::shared_ptr<fs::path>();
}
