#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <sstream>
#include <boost/thread/mutex.hpp>
#include <boost/filesystem.hpp>

/// A collection of utility methods */
class Util {
public:
    /// Converts arbitrary types into STL strings
    template<typename T>
    static std::string convert_to_string(const T& t)
    {
        std::stringstream ss;
        ss << t;
        return ss.str();
    }

    /// Presents a message to the user
    static void message(const std::string& message);

    /// Returns the directory of this program's binary
    static boost::filesystem::path bin_dir();

private:
    static boost::mutex message_mutex;
};

#endif
