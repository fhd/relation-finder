#ifndef FETCHER_HPP
#define FETCHER_HPP

#include <string>
#include <sstream>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include "graph.hpp"
#include "options.hpp"

/// Fetches relations from the database
class Fetcher {
public:
    class Connect_string_builder {
    public:
        void set_option(const std::string& name, const std::string& value);
        std::string string() const;

    private:
        std::stringstream stream;
    };

    /// Constructor
    Fetcher(boost::shared_ptr<Options> options);

    /// Returns the last read relations
    Graph::Graph_type get_relations() const;

    /// Fetches new relations from the database
    void fetch();

private:
    Graph::Graph_type relations;
    mutable boost::mutex relations_mutex;
    boost::shared_ptr<Options> options;
};

#endif
