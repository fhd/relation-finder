#include <string>
#include <pqxx/pqxx>
#include <boost/lexical_cast.hpp>
#include "options.hpp"
#include "util.hpp"
#include "logger.hpp"
#include "fetcher.hpp"

void Fetcher::Connect_string_builder::set_option(const std::string& name,
                                                 const std::string& value)
{
    if (!value.empty())
        stream << name << "=" << value << " ";
}

std::string Fetcher::Connect_string_builder::string() const
{
    return stream.str();
}

Fetcher::Fetcher(Options& options)
    : options(options)
{
}

Graph::Graph_type Fetcher::get_relations() const
{
    boost::mutex::scoped_lock lock(relations_mutex);
    return relations;
}

void Fetcher::fetch()
{
    boost::mutex::scoped_lock lock(relations_mutex);

    Logger::log("Fetching new relations from the database ...");

    relations.clear();

    // Connect to the database
    Connect_string_builder csb;
    csb.set_option("dbname", options.get_db_name());
    csb.set_option("user", options.get_db_user());
    csb.set_option("password", options.get_db_password());
    csb.set_option("host", options.get_db_host());
    csb.set_option("port", Util::convert_to_string<unsigned int>(
                                   options.get_db_port()));
    pqxx::connection connection(csb.string());
    pqxx::work work(connection);

    // Fetch all people
    pqxx::result presult = work.exec("select distinct owner_nr from buddys");
    for (pqxx::result::size_type i = 0; i < presult.size(); i++) {
        Graph::Node_type person_no;
        presult[i]["owner_nr"].to(person_no);

        // Read and store their friends
        Graph::Nodes_type& friends = relations[person_no];
        friends = Graph::Nodes_type();

        pqxx::result fresult =
            work.exec("select buddy_nr from buddys where owner_nr = "
                      + boost::lexical_cast<std::string>(person_no));
        for (pqxx::result::size_type j = 0; j < fresult.size(); j++) {
            Graph::Node_type friend_no;
            fresult[j]["buddy_nr"].to(friend_no);
            friends.push_back(friend_no);
        }
    }

    Logger::log("Fetched " + boost::lexical_cast<std::string>(presult.size())
                + " relations.");
}
