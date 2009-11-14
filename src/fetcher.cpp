#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include <boost/lexical_cast.hpp>
#include "options.hpp"
#include "util.hpp"
#include "fetcher.hpp"

boost::shared_ptr<fetcher> fetcher::instance_ = boost::shared_ptr<fetcher>();
boost::mutex fetcher::instance_mutex_;

boost::shared_ptr<fetcher> fetcher::instance()
{
	boost::mutex::scoped_lock lock(instance_mutex_);
	if (!instance_)
		instance_ = boost::shared_ptr<fetcher>(new fetcher());
	return instance_;
}

graph::graph_t fetcher::relations() const
{
	boost::mutex::scoped_lock lock(relations_mutex_);
	return relations_;
}

void fetcher::fetch()
{
	boost::mutex::scoped_lock lock(relations_mutex_);

	if (verbose_)
		std::cout << "Fetching new relations from the database ...";

	relations_.clear();

	// Connect to the database
	boost::shared_ptr<options> opts = options::instance();
	connect_string_builder csb;
	csb.set_option("dbname", opts->db_name());
	csb.set_option("user", opts->db_user());
	csb.set_option("password", opts->db_password());
	csb.set_option("host", opts->db_host());
	csb.set_option("port", util::convert_to_string<unsigned int>(
			opts->db_port()));
	pqxx::connection conn(csb.string());
	pqxx::work work(conn);

	// Fetch all people
	pqxx::result rpeople = work.exec("select distinct owner_nr from buddys");
	for (pqxx::result::size_type i = 0; i < rpeople.size(); i++) {
		graph::node_t person_no;
		rpeople[i]["owner_nr"].to(person_no);
		relations_[person_no] = graph::nodes_t();
		graph::nodes_t &friends = relations_[person_no];

		// Read and store their friends
		pqxx::result rfriends = work.exec(
				"select buddy_nr from buddys where owner_nr = "
				+ boost::lexical_cast<std::string>(person_no));

		for (pqxx::result::size_type j = 0; j < rfriends.size(); j++) {
			graph::node_t friend_no;
			rfriends[j]["buddy_nr"].to(friend_no);
			friends.push_back(friend_no);
		}
	}

	if (verbose_)
		std::cout << " finished." << std::endl;
}

fetcher::fetcher() : verbose_(options::instance()->verbose())
{
}

void fetcher::connect_string_builder::set_option(const std::string &name,
		const std::string &value)
{
	if (!value.empty())
		stream_ << name << "=" << value << " ";
}

std::string fetcher::connect_string_builder::string() const
{
	return stream_.str();
}
