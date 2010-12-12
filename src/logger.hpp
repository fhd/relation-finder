#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>

/// The logging system
class Logger {
public:
    /// Controls whether output should be verbose
    static bool verbose;

    /// Presents a message to the user
    static void log(const std::string& message);
};

#endif
