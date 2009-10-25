#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <sstream>

/** A class containing utility methods */
class util
{
public:
	template<class T>
	static std::string convert_to_string(const T &t)
	{
		std::stringstream ss;
		ss << t;
		return ss.str();
	}
};

#endif /* UTIL_HPP */
