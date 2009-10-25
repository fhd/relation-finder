#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/filesystem.hpp>

/** Reads and provides program options */
class options
{
public:
	/** Singleton instance getter */
	static boost::shared_ptr<options> get_instance();

	/** Parses options from the command line and the configuration file */
	void parse(int argc, char **argv);

	unsigned int get_port();
	unsigned int get_fetching_interval();
	unsigned int get_depth_limit();
	bool get_verbose();
	std::string get_db_name();
	std::string get_db_user();
	std::string get_db_password();
	std::string get_db_host();
	unsigned int get_db_port();

private:
	static boost::shared_ptr<options> instance_;
	static boost::mutex instance_mutex_;
	boost::mutex options_mutex_;
	unsigned int port_;
	unsigned int fetching_interval_;
	unsigned int depth_limit_;
	bool verbose_;
	std::string db_name_;
	std::string db_user_;
	std::string db_password_;
	std::string db_host_;
	unsigned int db_port_;

	options();

	/** Looks for the configuration file in several reasonable locations */
	boost::shared_ptr<boost::filesystem::path> find_config_file(
			char *binary_path);
};

#endif /* OPTIONS_HPP */
