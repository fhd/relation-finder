#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include <asio.hpp>
#include "tcp_connection.hpp"

class Tcp_server {
public:
    /// Constructor creating a new multi-client server
    Tcp_server(asio::io_service& io_service, unsigned int port,
               boost::shared_ptr<Fetcher> fetcher, unsigned int depth_limit);

private:
    asio::ip::tcp::acceptor acceptor;
    boost::shared_ptr<Fetcher> fetcher;
    unsigned int depth_limit;

    void start_accept();
    void handle_accept(boost::shared_ptr<Tcp_connection> new_connection,
                       const asio::error_code& error);
};

#endif
