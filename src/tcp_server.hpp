#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include <asio.hpp>
#include "tcp_connection.hpp"

class tcp_server
{
	public:
		/**
		 * Constructor creating a new multiclient server using the supplied
		 * depth limit when invoking the search algorithm.
		 */
		tcp_server(asio::io_service &io_service, unsigned int port,
				unsigned int depth_limit);

	private:
		asio::ip::tcp::acceptor acceptor_;
		unsigned int depth_limit_;

		void start_accept();
		void handle_accept(boost::shared_ptr<tcp_connection> new_connection,
				const asio::error_code &error);
};

#endif /* TCP_SERVER_HPP */
