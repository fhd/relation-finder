#include "server.hpp"

void server::listen(unsigned int port)
{
	// TODO: Asset that the port lies in the allowed range
	asio::io_service io_service;
	tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), port));
	
	for (;;) {
		// Accept a connection
		tcp::socket socket(io_service);
		acceptor.accept(socket);

		// Talk with the client
		// TODO: How are the clients cleaned up?
		client *c = new client(socket);
		c->start();
	}
}
