#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <boost/enable_shared_from_this.hpp>
#include <asio.hpp>

/// A communication with a client
class Tcp_connection : public boost::enable_shared_from_this<Tcp_connection> {
public:
    /**
     * Constructor creating a new connection that returns paths up to the
     * @a depth_limit from relations of the @a fetcher
     */
    Tcp_connection(asio::io_service& io_service,
                   boost::shared_ptr<Fetcher> fetcher,
                   unsigned int depth_limit);

    asio::ip::tcp::socket& get_socket();

    /// Commences the communication
    void start();

private:
    asio::ip::tcp::socket socket;
    boost::shared_ptr<Fetcher> fetcher;
    unsigned int depth_limit;

    uint32_t read_uint();
    void write_uint(uint32_t uint);
};

#endif
