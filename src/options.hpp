#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <string>
#include <boost/thread/mutex.hpp>

namespace boost {
    namespace program_options {
        class options_description;
    }
}

/// Reads and provides program options
class Options {
public:
    /**
     * Constructor that parses options from the command line and the
     * configuration file
     * \throws int If execution should be aborted, where the integer is the
     *             proposed return code for the program
     */
    Options(int argc, char* argv[]);

    unsigned int get_port() const;
    unsigned int get_fetching_interval() const;
    unsigned int get_depth_limit() const;
    bool get_verbose() const;
    std::string get_db_name() const;
    std::string get_db_user() const;
    std::string get_db_password() const;
    std::string get_db_host() const;
    unsigned int get_db_port() const;

private:
    mutable boost::mutex options_mutex;
    unsigned int port;
    unsigned int fetching_interval;
    unsigned int depth_limit;
    bool verbose;
    std::string db_name;
    std::string db_user;
    std::string db_password;
    std::string db_host;
    unsigned int db_port;

    boost::program_options::options_description create_description();
};

#endif
