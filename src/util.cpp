#include <iostream>
#include "options.hpp"
#include "util.hpp"

boost::mutex util::message_mutex_;

void util::message(const std::string &s)
{
	if (options::instance()->verbose()) {
		boost::mutex::scoped_lock lock(message_mutex_);
		std::cout << s << std::endl;
	}
}
