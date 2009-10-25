#include <iostream>
#include <soci/soci.h>
#include <soci/postgresql/soci-postgresql.h>
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
	SOCI::Session sql(SOCI::postgresql, csb.string());

	// Fetch all people
	int person_no;
	SOCI::Statement pst = (sql.prepare
			<< "select distinct owner_nr from buddys",
			SOCI::into(person_no));
	pst.execute();

	// Read and store their friends
	while (pst.fetch()) {
		relations_[person_no] = graph::nodes_t();
		graph::nodes_t &friends = relations_[person_no];

		int friend_no;
		SOCI::Statement fst = (sql.prepare
				<< "select buddy_nr from buddys where owner_nr = :person_no",
				SOCI::use(person_no), SOCI::into(friend_no));
		fst.execute();

		while (fst.fetch())
			friends.push_back(friend_no);
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

std::string fetcher::connect_string_builder::string()
{
	return stream_.str();
}
