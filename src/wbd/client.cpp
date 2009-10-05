#include "client.hpp"

client::client(tcp::socket &socket)
: m_socket(socket)
{
}

client::~client()
{
}

void client::run()
{
	// read the person's id
	unsigned int pid = read_uint();

	// read the friend's id
	unsigned int fid = read_uint();

	// get the current relations and calculate the path
	graph::graph_t relations = fetcher::get_instance()->get_relations();
	searcher searcher(relations);
	// TODO: Make the depth limit a command line option
	graph::path_t *path = searcher.find_shortest_path(pid, fid, 5);
	int path_length;
	if (path == NULL)
		path_length = 0;
	else
		path_length = path->size();

	// write the path length
	write_uint(path_length);

	// write the path
	for (int i = 0; i < path_length; i++) {
		write_uint(path->at(i));
	}
}

unsigned int client::read_uint()
{
	asio::error_code error;
	unsigned int uint;
	m_socket.read_some(asio::buffer((void *) &uint, sizeof(uint)), error);
	if (error)
		throw asio::system_error(error);
	return uint;
}

void client::write_uint(unsigned int uint)
{
	asio::error_code error;
	m_socket.write_some(asio::buffer((void *) &uint, sizeof(uint)), error);
	if (error)
		throw asio::system_error(error);
}
