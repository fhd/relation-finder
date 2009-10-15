#include <boost/bind.hpp>
#include "tcp_server.hpp"

using asio::ip::tcp;

tcp_server::tcp_server(asio::io_service &io_service, unsigned int port,
		unsigned int depth_limit) :
		acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
		depth_limit_(depth_limit)
{
	start_accept();
}

void tcp_server::start_accept()
{
	boost::shared_ptr<tcp_connection> new_connection = tcp_connection::create(
			acceptor_.io_service(), depth_limit_);

	acceptor_.async_accept(new_connection->get_socket(),
			boost::bind(&tcp_server::handle_accept, this, new_connection,
				asio::placeholders::error));
}

void tcp_server::handle_accept(
		boost::shared_ptr<tcp_connection> new_connection,
		const asio::error_code &error)
{
	if (!error) {
		new_connection->start();
		start_accept();
	}
}
