#include <boost/bind.hpp>
#include "logger.hpp"
#include "fetcher.hpp"
#include "tcp_server.hpp"

using asio::ip::tcp;

Tcp_server::Tcp_server(asio::io_service& io_service, unsigned int port,
                       Fetcher& fetcher, unsigned int depth_limit)
    : acceptor(io_service, tcp::endpoint(tcp::v4(), port)), fetcher(fetcher),
      depth_limit(depth_limit)
{
    Logger::log("Accepting connections.");
    start_accept();
}

void Tcp_server::start_accept()
{
    boost::shared_ptr<asio::ip::tcp::socket> socket(
            new asio::ip::tcp::socket(acceptor.io_service()));
    boost::shared_ptr<Tcp_connection> new_connection(
            new Tcp_connection(socket, fetcher, depth_limit));

    acceptor.async_accept(*socket, boost::bind(&Tcp_server::handle_accept, this,
                                               new_connection,
                                               asio::placeholders::error));
}

void Tcp_server::handle_accept(boost::shared_ptr<Tcp_connection> new_connection,
                               const asio::error_code& error)
{
    Logger::log("New connection.");

    if (!error) {
        new_connection->start();
        start_accept();
    }
}
