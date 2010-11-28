#include <boost/bind.hpp>
#include "util.hpp"
#include "tcp_server.hpp"

using asio::ip::tcp;

Tcp_server::Tcp_server(asio::io_service& io_service, unsigned int port)
    : acceptor(io_service, tcp::endpoint(tcp::v4(), port))
{
    Util::message("Accepting connections.");
    start_accept();
}

void Tcp_server::start_accept()
{
    boost::shared_ptr<Tcp_connection> new_connection =
        Tcp_connection::create(acceptor.io_service());

    acceptor.async_accept(new_connection->get_socket(),
                          boost::bind(&Tcp_server::handle_accept,
                                      this, new_connection,
                                      asio::placeholders::error));
}

void Tcp_server::handle_accept(boost::shared_ptr<Tcp_connection> new_connection,
                               const asio::error_code& error)
{
    Util::message("New connection.");

    if (!error) {
        new_connection->start();
        start_accept();
    }
}
