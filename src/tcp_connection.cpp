#include "fetcher.hpp"
#include "tcp_connection.hpp"

boost::shared_ptr<tcp_connection> tcp_connection::create(
		asio::io_service &io_service, unsigned int depth_limit)
{
	return boost::shared_ptr<tcp_connection>(
			new tcp_connection(io_service, depth_limit));
}

asio::ip::tcp::socket &tcp_connection::socket()
{
	return socket_;
}

void tcp_connection::start()
{
	// Read the person's id
	uint32_t pid = read_uint();

	// Read the other person's id
	uint32_t apid = read_uint();

	// Get the current relations and calculate the path
	graph::graph_t relations = fetcher::instance()->relations();
	searcher searcher(relations);
	boost::shared_ptr<graph::path_t> path = searcher.find_shortest_path(
			pid, apid, depth_limit_);

	uint32_t path_length = !path ? 0 : path->size();

	// Write the path length
	write_uint(path_length);

	// Write the path
	for (uint32_t i = 0; i < path_length; i++)
		write_uint(path->at(i));
}

tcp_connection::tcp_connection(asio::io_service &io_service,
		unsigned int depth_limit) : socket_(io_service),
		depth_limit_(depth_limit)
{
}

uint32_t tcp_connection::read_uint()
{
	asio::error_code error;
	uint32_t uint;
	socket_.read_some(asio::buffer((void *) &uint, sizeof(uint)), error);
	if (error)
		throw asio::system_error(error);
	return uint;
}

void tcp_connection::write_uint(uint32_t uint)
{
	asio::error_code error;
	socket_.write_some(asio::buffer((void *) &uint, sizeof(uint)), error);
	if (error)
		throw asio::system_error(error);
}
