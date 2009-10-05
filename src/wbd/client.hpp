#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <boost/foreach.hpp>
#include <asio.hpp>
#include "thread.hpp"
#include "fetcher.hpp"

using asio::ip::tcp;

/** A thread handling a client */
class client : public thread
{
public:
	/** Constructor that sets the socket used for communication */
	client(tcp::socket &socket);

	/** Destructor */
	~client();

private:
	tcp::socket &m_socket;

	void run();
	unsigned int read_uint();
	void write_uint(unsigned int uint);
};

#endif /* CLIENT_HPP */
