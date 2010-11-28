#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <boost/enable_shared_from_this.hpp>
#include <asio.hpp>

/// A communication with a client
class Tcp_connection : public boost::enable_shared_from_this<Tcp_connection> {
public:
    /// Creates a new connection
    static boost::shared_ptr<Tcp_connection> create(
            asio::io_service& io_service);

    asio::ip::tcp::socket& get_socket();

    /// Commences the communication
    void start();

private:
    asio::ip::tcp::socket socket;
    unsigned int depth_limit;

    Tcp_connection(asio::io_service& io_service);
    uint32_t read_uint();
    void write_uint(uint32_t uint);
};

#endif
