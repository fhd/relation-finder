#include <iostream>
#include <fstream>
#include <vector>
#include <boost/program_options.hpp>
#include <boost/foreach.hpp>
#include "options.hpp"
#include "util.hpp"

#define VERSION "2.2.0"
#define DESCRIPTION_TEXT "A daemon that finds the shortest path between two " \
    "people in a social network."
#define USAGE_TEXT "Usage: relation-finder [OPTION]..."
#define VERSION_TEXT "relation-finder "VERSION"\n"  \
    "Copyright (C) 2009 Felix H. Dahlke.\n"         \
    "Licensed under the MIT License."

#define CONFIG_FILE "relation-finder.cfg"
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

boost::shared_ptr<fs::path> find_config_file(const char* binary_path)
{
    // The following candidates will be searched in that order
    std::vector<fs::path> candidates;
    candidates.push_back(Util::bin_dir() / "/../etc/"CONFIG_FILE);
    candidates.push_back("/etc/"CONFIG_FILE);

    // Check each of the candidates and return the first one that is found
    BOOST_FOREACH(fs::path candidate, candidates)
        if (fs::exists(candidate))
            return boost::shared_ptr<fs::path>(new fs::path(candidate));

    return boost::shared_ptr<fs::path>();
}

Options::Options(int argc, char* argv[])
{
    boost::mutex::scoped_lock lock(options_mutex);

    po::options_description desc("Options");
    desc.add_options()
        ("port", po::value<unsigned int>(&port)
         ->default_value(DEFAULT_PORT),
         "set the tcp port to listen on")
        ("fetching-interval", po::value<unsigned int>(&fetching_interval)
         ->default_value(DEFAULT_FETCHING_INTERVAL),
         "set the time (in seconds) to wait before fetching new \
relations from the database")
        ("depth-limit", po::value<unsigned int>(&depth_limit)
         ->default_value(DEFAULT_DEPTH_LIMIT),
         "set the maximum length of relationship paths")
        ("db-name", po::value<std::string>(&db_name)
         ->default_value(DEFAULT_DB_NAME), "set the database name")
        ("db-user", po::value<std::string>(&db_user)
         ->default_value(DEFAULT_DB_USER), "set the database user")
        ("db-password", po::value<std::string>(&db_password)
         ->default_value(DEFAULT_DB_PASSWORD),
         "set the database user's password")
        ("db-host", po::value<std::string>(&db_host)
         ->default_value(DEFAULT_DB_HOST), "set the database host")
        ("db-port", po::value<unsigned int>(&db_port)
         ->default_value(DEFAULT_DB_PORT), "set the database port")
        ("verbose", "explain what is happening")
        ("help", "display this help and exit")
        ("version", "output version information and exit");

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

    verbose = vm.count("verbose");
}

unsigned int Options::get_port() const
{
    boost::mutex::scoped_lock lock(options_mutex);
    return port;
}

unsigned int Options::get_fetching_interval() const
{
    boost::mutex::scoped_lock lock(options_mutex);
    return fetching_interval;
}

unsigned int Options::get_depth_limit() const
{
    boost::mutex::scoped_lock lock(options_mutex);
    return depth_limit;
}

bool Options::get_verbose() const
{
    boost::mutex::scoped_lock lock(options_mutex);
    return verbose;
}

std::string Options::get_db_name() const
{
    boost::mutex::scoped_lock lock(options_mutex);
    return db_name;
}

std::string Options::get_db_user() const
{
    boost::mutex::scoped_lock lock(options_mutex);
    return db_user;
}

std::string Options::get_db_password() const
{
    boost::mutex::scoped_lock lock(options_mutex);
    return db_password;
}

std::string Options::get_db_host() const
{
    boost::mutex::scoped_lock lock(options_mutex);
    return db_host;
}

unsigned int Options::get_db_port() const
{
    boost::mutex::scoped_lock lock(options_mutex);
    return db_port;
}
