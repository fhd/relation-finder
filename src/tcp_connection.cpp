#include "fetcher.hpp"
#include "tcp_connection.hpp"

boost::shared_ptr<tcp_connection> tcp_connection::create(
		asio::io_service &io_service)
{
	return boost::shared_ptr<tcp_connection>(
			new tcp_connection(io_service));
}

asio::ip::tcp::socket &tcp_connection::get_socket()
{
	return socket_;
}

void tcp_connection::start()
{
	// read the person's id
	unsigned int pid = read_uint();

	// read the friend's id
	unsigned int fid = read_uint();

	// get the current relations and calculate the path
	graph::graph_t relations = fetcher::get_instance()->get_relations();
	searcher searcher(relations);
	// TODO: Make the depth limit a command line option
	boost::shared_ptr<graph::path_t> path = searcher.find_shortest_path(
			pid, fid, 5);
	int path_length = !path ? 0 : path->size();

	// write the path length
	write_uint(path_length);

	// write the path
	for (int i = 0; i < path_length; i++)
		write_uint(path->at(i));
}

tcp_connection::tcp_connection(asio::io_service &io_service)
: socket_(io_service)
{
}

unsigned int tcp_connection::read_uint()
{
	asio::error_code error;
	unsigned int uint;
	socket_.read_some(asio::buffer((void *) &uint, sizeof(uint)), error);
	if (error)
		throw asio::system_error(error);
	return uint;
}

void tcp_connection::write_uint(unsigned int uint)
{
	asio::error_code error;
	socket_.write_some(asio::buffer((void *) &uint, sizeof(uint)), error);
	if (error)
		throw asio::system_error(error);
}
