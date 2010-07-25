#include <iostream>
#include <fstream>
#include <vector>
#include <boost/program_options.hpp>
#include <boost/foreach.hpp>
#include "options.hpp"
#include "util.hpp"

#define VERSION "0.2"
#define DESCRIPTION_TEXT \
		"A daemon calculating the shortest path between two people " \
		"in a social network."
#define USAGE_TEXT "Usage: wbd [OPTION]..."
#define VERSION_TEXT \
		"wbd (Wanjas Beziehungs Daemon) "VERSION"\n" \
		"Copyright (C) 2009 Felix H. Dahlke.\n" \
		"Licensed under the MIT License."

#define CONFIG_FILE "wbd.cfg"
#define DEFAULT_PORT 8888
#define DEFAULT_FETCHING_INTERVAL 300
#define DEFAULT_DEPTH_LIMIT 5
#define DEFAULT_DB_NAME ""
#define DEFAULT_DB_USER ""
#define DEFAULT_DB_PASSWORD ""
#define DEFAULT_DB_HOST "localhost"
#define DEFAULT_DB_PORT 5432

namespace fs = boost::filesystem;
namespace po = boost::program_options;

boost::shared_ptr<options> options::instance_ = boost::shared_ptr<options>();
boost::mutex options::instance_mutex_;

boost::shared_ptr<options> options::instance()
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
			("port", po::value<unsigned int>(&port_)
					->default_value(DEFAULT_PORT),
					"set the tcp port to listen on")
			("fetching-interval", po::value<unsigned int>(&fetching_interval_)
					->default_value(DEFAULT_FETCHING_INTERVAL),
					"set the time (in seconds) to wait before fetching new \
relations from the database")
			("depth-limit", po::value<unsigned int>(&depth_limit_)
					->default_value(DEFAULT_DEPTH_LIMIT),
					"set the maximum length of relationship paths")
			("db-name", po::value<std::string>(&db_name_)
					->default_value(DEFAULT_DB_NAME), "set the database name")
			("db-user", po::value<std::string>(&db_user_)
					->default_value(DEFAULT_DB_USER), "set the database user")
			("db-password", po::value<std::string>(&db_password_)
					->default_value(DEFAULT_DB_PASSWORD),
					"set the database user's password")
			("db-host", po::value<std::string>(&db_host_)
					->default_value(DEFAULT_DB_HOST), "set the database host")
			("db-port",	po::value<unsigned int>(&db_port_)
					->default_value(DEFAULT_DB_PORT), "set the database port")
			("verbose", "explain what is happening")
			("help", "display this help and exit")
			("version",	"output version information and exit");

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

unsigned int options::port() const
{
	boost::mutex::scoped_lock lock(options_mutex_);
	return port_;
}

unsigned int options::fetching_interval() const
{
	boost::mutex::scoped_lock lock(options_mutex_);
	return fetching_interval_;
}

unsigned int options::depth_limit() const
{
	boost::mutex::scoped_lock lock(options_mutex_);
	return depth_limit_;
}

bool options::verbose() const
{
	boost::mutex::scoped_lock lock(options_mutex_);
	return verbose_;
}

std::string options::db_name() const
{
	boost::mutex::scoped_lock lock(options_mutex_);
	return db_name_;
}

std::string options::db_user() const
{
	boost::mutex::scoped_lock lock(options_mutex_);
	return db_user_;
}

std::string options::db_password() const
{
	boost::mutex::scoped_lock lock(options_mutex_);
	return db_password_;
}

std::string options::db_host() const
{
	boost::mutex::scoped_lock lock(options_mutex_);
	return db_host_;
}

unsigned int options::db_port() const
{
	boost::mutex::scoped_lock lock(options_mutex_);
	return db_port_;
}

options::options()
{
}

boost::shared_ptr<fs::path> options::find_config_file(
		const char *binary_path) const
{
	// The following candidates will be searched in that order
	std::vector<fs::path> candidates;
	candidates.push_back(util::bin_dir() / "/../etc/"CONFIG_FILE);
	candidates.push_back("/etc/"CONFIG_FILE);

	// Check each of the candidates and return the first one that is found
	BOOST_FOREACH(fs::path candidate, candidates)
		if (fs::exists(candidate))
			return boost::shared_ptr<fs::path>(new fs::path(candidate));

	return boost::shared_ptr<fs::path>();
}
