#include <string>
#include <pqxx/pqxx>
#include <boost/lexical_cast.hpp>
#include "options.hpp"
#include "util.hpp"
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

boost::shared_ptr<Fetcher> Fetcher::instance = boost::shared_ptr<Fetcher>();
boost::mutex Fetcher::instance_mutex;

boost::shared_ptr<Fetcher> Fetcher::get_instance()
{
    boost::mutex::scoped_lock lock(instance_mutex);
    if (!instance)
        instance = boost::shared_ptr<Fetcher>(new Fetcher());
    return instance;
}

Graph::graph_t Fetcher::get_relations() const
{
    boost::mutex::scoped_lock lock(relations_mutex);
    return relations;
}

void Fetcher::fetch()
{
    boost::mutex::scoped_lock lock(relations_mutex);

    Util::message("Fetching new relations from the database ...");

    relations.clear();

    // Connect to the database
    boost::shared_ptr<Options> opts = Options::get_instance();
    Connect_string_builder csb;
    csb.set_option("dbname", opts->get_db_name());
    csb.set_option("user", opts->get_db_user());
    csb.set_option("password", opts->get_db_password());
    csb.set_option("host", opts->get_db_host());
    csb.set_option("port",
                   Util::convert_to_string<unsigned int>(opts->get_db_port()));
    pqxx::connection connection(csb.string());
    pqxx::work work(connection);

    // Fetch all people
    pqxx::result presult = work.exec("select distinct owner_nr from buddys");
    for (pqxx::result::size_type i = 0; i < presult.size(); i++) {
        Graph::node_t person_no;
        presult[i]["owner_nr"].to(person_no);

        // Read and store their friends
        Graph::nodes_t& friends = relations[person_no];
        friends = Graph::nodes_t();

        pqxx::result fresult =
            work.exec("select buddy_nr from buddys where owner_nr = "
                      + boost::lexical_cast<std::string>(person_no));
        for (pqxx::result::size_type j = 0; j < fresult.size(); j++) {
            Graph::node_t friend_no;
            fresult[j]["buddy_nr"].to(friend_no);
            friends.push_back(friend_no);
        }
    }

    Util::message("Fetched "
                  + boost::lexical_cast<std::string>(presult.size())
                  + " relations.");
}

Fetcher::Fetcher()
{
}
