#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/filesystem.hpp>

/// Reads and provides program options
class Options {
public:
    /// Singleton instance getter
    static boost::shared_ptr<Options> get_instance();

    /**
     * Parses options from the command line and the configuration file.
     * Throws an integer exception if execution should be aborted, where the
     * integer is the proposed return code for the program.
     */
    void parse(int argc, char* argv[]);

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
    static boost::shared_ptr<Options> instance;
    static boost::mutex instance_mutex;
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

    Options();
};

#endif
