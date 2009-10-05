#include <string>
#include <iostream>
#include <boost/array.hpp>
#include <asio.hpp>

#define HOST "localhost"
#define PORT 8888

using asio::ip::tcp;

unsigned int read_uint(tcp::socket &socket)
{
	asio::error_code error;
	unsigned int uint;
	socket.read_some(asio::buffer((void *) &uint, sizeof(uint)), error);
	if (error)
		throw asio::system_error(error);
	return uint;
}

void write_uint(tcp::socket &socket, unsigned int uint)
{
	asio::error_code error;
	socket.write_some(asio::buffer((void *) &uint, sizeof(uint)), error);
	if (error)
		throw asio::system_error(error);
}

int main(int argc, char *argv[])
{
	std::string host, port;
	unsigned int pid, fid;
	std::cout << "WBD's host: ";
	std::cin >> host;
	std::cout << "WBD's port: ";
	std::cin >> port;
	std::cout << "Your ID: ";
	std::cin >> pid;
	std::cout << "Your friend's ID: ";
	std::cin >> fid;

	try {
		// resolve the host
		asio::io_service io_service;
		tcp::resolver resolver(io_service);
		tcp::resolver::query query(host, port);
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		tcp::resolver::iterator end;

		// connect to the server
		tcp::socket socket(io_service);
		asio::error_code error = asio::error::host_not_found;
		while (error && endpoint_iterator != end) {
			socket.close();
			socket.connect(*endpoint_iterator++, error);
		}
		if (error)
			throw asio::system_error(error);

		// write the person's id
		write_uint(socket, pid);

		// write the friend's id
		write_uint(socket, fid);

		// read the lenght of the path
		int path_length = read_uint(socket);
		if (path_length == 0) {
			std::cout << "no path was found." << std::endl;
		} else {
			std::cout << "found a path: ";
			for (int i = 0; i < path_length; i++) {
				unsigned int node = read_uint(socket);
				std::cout << node;
				if (i != path_length - 1)
					std::cout << " -> ";
			}
			std::cout << std::endl;
		}
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
