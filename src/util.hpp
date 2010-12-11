#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <sstream>
#include <boost/thread/mutex.hpp>
#include <boost/filesystem.hpp>

/// A collection of utility methods */
namespace Util {
    /// Controls whether output should be verbose
    extern bool verbose;

    /// Converts arbitrary types into STL strings
    template<typename T>
    std::string convert_to_string(const T& t)
    {
        std::stringstream ss;
        ss << t;
        return ss.str();
    }

    /// Presents a message to the user
    void message(const std::string& message);

    /// Returns the directory of this program's binary
    boost::filesystem::path bin_dir();
}

#endif
