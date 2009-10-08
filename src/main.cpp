#include <iostream>
#include <asio.hpp>
#include "fetcher.hpp"
#include "tcp_server.hpp"

int main(int argc, char **argv)
{
	/*
	 * TODO: Read the following from options:
	 * - the server's port
	 * - the searcher's depth limit
	 * - the fetcher's sleeping time
	 *
	 * TODO: Handle signals properly
	 */

	// start the fetcher
	fetcher *fetcher = fetcher::get_instance();
	// TODO: Run as a thread
	fetcher->fetch();

	// start the server to listen for incoming connections
	try {
		asio::io_service io_service;
		tcp_server server(io_service, 8888);
		io_service.run();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
