#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include <asio.hpp>
#include "tcp_connection.hpp"

class tcp_server
{
	public:
		tcp_server(asio::io_service &io_service, unsigned int port);

	private:
		void start_accept();
		void handle_accept(boost::shared_ptr<tcp_connection> new_connection,
				const asio::error_code &error);

		asio::ip::tcp::acceptor acceptor_;
};

#endif /* TCP_SERVER_HPP */