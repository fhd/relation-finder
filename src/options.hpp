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
	static boost::shared_ptr<options> instance();

	/**
	 * Parses options from the command line and the configuration file.
	 * Throws an integer exception if execution should be aborted, where the
	 * integer is the proposed return code for the program.
	 */
	void parse(int argc, char **argv);

	unsigned int port() const;
	unsigned int fetching_interval() const;
	unsigned int depth_limit() const;
	bool verbose() const;
	std::string db_name() const;
	std::string db_user() const;
	std::string db_password() const;
	std::string db_host() const;
	unsigned int db_port() const;

private:
	static boost::shared_ptr<options> instance_;
	static boost::mutex instance_mutex_;
	mutable boost::mutex options_mutex_;
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
			const char *binary_path) const;
};

#endif /* OPTIONS_HPP */
