#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <boost/enable_shared_from_this.hpp>
#include <asio.hpp>

/** A communication with a client */
class tcp_connection : public boost::enable_shared_from_this<tcp_connection>
{
public:
	/** Creates a new connection */
	static boost::shared_ptr<tcp_connection> create(
			asio::io_service &io_service);

	asio::ip::tcp::socket &get_socket();

	/** Commences the communication */
	void start();

private:
	asio::ip::tcp::socket socket_;

	tcp_connection(asio::io_service &io_service);
	unsigned int read_uint();
	void write_uint(unsigned int uint);
};

#endif /* CLIENT_HPP */