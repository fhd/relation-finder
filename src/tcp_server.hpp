#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include <asio.hpp>
#include "tcp_connection.hpp"

class Tcp_server {
public:
    /// Constructor creating a new multiclient server
    Tcp_server(asio::io_service& io_service, unsigned int port);

private:
    asio::ip::tcp::acceptor acceptor;

    void start_accept();
    void handle_accept(boost::shared_ptr<Tcp_connection> new_connection,
                       const asio::error_code& error);
};

#endif
