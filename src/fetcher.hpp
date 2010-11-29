#ifndef FETCHER_HPP
#define FETCHER_HPP

#include <string>
#include <sstream>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include "graph.hpp"

/// Reads relations regularly from the database
class Fetcher {
public:
    class Connect_string_builder {
    public:
        void set_option(const std::string& name, const std::string& value);
        std::string string() const;

    private:
        std::stringstream stream;
    };

    /// Singleton instance getter
    static boost::shared_ptr<Fetcher> get_instance();

    /// Returns the last read relations
    Graph::Graph_type get_relations() const;

    /// Fetches new relations from the database regularly
    void fetch();

private:
    static boost::shared_ptr<Fetcher> instance;
    static boost::mutex instance_mutex;
    Graph::Graph_type relations;
    mutable boost::mutex relations_mutex;

    Fetcher();
};

#endif
