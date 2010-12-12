#include <iostream>
#include <boost/thread/mutex.hpp>
#include "logger.hpp"

bool Logger::verbose = false;

boost::mutex message_mutex;

void Logger::log(const std::string& message)
{
    if (!verbose)
        return;

    boost::mutex::scoped_lock lock(message_mutex);
    std::cout << message << std::endl;
}
