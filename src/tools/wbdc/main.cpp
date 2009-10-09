/*
 * This is an example client for wbd, demonstrating its protocol
 * using Boost.Asio for network communication.
 *
 * The protocol is pretty simple, the only data send is a couple of
 * 32 bit unsigned integers. It basically works like this:
 * 1. Connect to wbd via TCP.
 * 2. Send the user ID of the first person (user A).
 * 3. Send the user ID of the second person (user B).
 * 4. Read the length of path.
 *    If that number is 0, no path could be found.
 * 5. Read as many user IDs as the path was long.
 *    This is the result, the path from user A to user B.
 */

#include <string>
#include <iostream>
#include <boost/array.hpp>
#include <asio.hpp>

using asio::ip::tcp;

/** Utility method for reading an unsigned integer */
uint32_t read_uint(tcp::socket &socket)
{
	asio::error_code error;
	uint32_t uint;
	socket.read_some(asio::buffer((void *) &uint, sizeof(uint)), error);
	if (error)
		throw asio::system_error(error);
	return uint;
}

/** Utility method for writing an unsigned integer */
void write_uint(tcp::socket &socket, uint32_t uint)
{
	asio::error_code error;
	socket.write_some(asio::buffer((void *) &uint, sizeof(uint)), error);
	if (error)
		throw asio::system_error(error);
}

int main(int argc, char *argv[])
{
	// Read request parameters from stdin
	std::string host, port;
	unsigned int pid, apid;
	std::cout << "This tool will ask wbd for a connection between two people."
			<< std::endl;
	std::cout << "wbd's host: ";
	std::cin >> host;
	std::cout << "wbd's port: ";
	std::cin >> port;
	std::cout << "A person's ID: ";
	std::cin >> pid;
	std::cout << "Another person's ID: ";
	std::cin >> apid;

	try {
		// Resolve the host
		asio::io_service io_service;
		tcp::resolver resolver(io_service);
		tcp::resolver::query query(host, port);
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		tcp::resolver::iterator end;

		// Connect to the server
		tcp::socket socket(io_service);
		asio::error_code error = asio::error::host_not_found;
		while (error && endpoint_iterator != end) {
			socket.close();
			socket.connect(*endpoint_iterator++, error);
		}
		if (error)
			throw asio::system_error(error);

		// Write the person's id
		write_uint(socket, pid);

		// Write the other person's id
		write_uint(socket, apid);

		// Read the length of the path
		int path_length = read_uint(socket);
		if (path_length == 0) {
			std::cout << "No path was found." << std::endl;
		} else {
			std::cout << "Found a path: ";

			// Read the path
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
