#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <sstream>
#include <boost/thread/mutex.hpp>

/** A class containing utility methods */
class util
{
public:
	/** Converts arbitrary types into STL strings */
	template<typename T>
	static std::string convert_to_string(const T &t)
	{
		std::stringstream ss;
		ss << t;
		return ss.str();
	}

	/** Presents a message to the user */
	static void message(const std::string &message);

private:
	static boost::mutex message_mutex_;
};

#endif /* UTIL_HPP */
