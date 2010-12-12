#ifndef FETCHER_HPP
#define FETCHER_HPP

#include <string>
#include <sstream>
#include <boost/thread/mutex.hpp>
#include "graph.hpp"
#include "options.hpp"

/// Fetches relations from the database
class Fetcher {
public:
    class Connect_string_builder {
    public:
        void set_option(const std::string& name, const std::string& value);
        std::string get_string() const;

    private:
        std::stringstream stream;
    };

    /// Constructor
    Fetcher(Options& options);

    /// Returns the last read relations
    Graph::Graph_type get_relations() const;

    /// Fetches new relations from the database
    void fetch();

private:
    Graph::Graph_type relations;
    mutable boost::mutex relations_mutex;
    Options& options;
};

#endif
