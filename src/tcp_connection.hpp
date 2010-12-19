#ifndef TCP_CONNECTION_HPP
#define TCP_CONNECTION_HPP

#include <asio.hpp>

/// A communication with a client
class Tcp_connection {
public:
    /**
     * Constructor creating a new connection that returns paths up to the
     * @a depth_limit from relations of the @a fetcher
     */
    Tcp_connection(boost::shared_ptr<asio::ip::tcp::socket> socket,
                   Fetcher& fetcher, unsigned int depth_limit);

    /// Commences the communication
    void start();

private:
    boost::shared_ptr<asio::ip::tcp::socket> socket;
    Fetcher& fetcher;
    unsigned int depth_limit;

    uint32_t read_uint();
    void write_uint(uint32_t uint);
};

#endif
