#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <asio.hpp>
#include "client.hpp"

using asio::ip::tcp;

/** Accepts and delegates incoming connections */
class server
{
public:
	void listen(unsigned int);
};

#endif /* SERVER_HPP */
