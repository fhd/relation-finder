#include "server.hpp"

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
	fetcher->start();

	// start the server to listen for incoming connections
	server s;
	try {
		s.listen(8888);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
