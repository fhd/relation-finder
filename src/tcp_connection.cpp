#include "options.hpp"
#include "fetcher.hpp"
#include "searcher.hpp"
#include "tcp_connection.hpp"

boost::shared_ptr<Tcp_connection> Tcp_connection::create(
        asio::io_service& io_service)
{
    return boost::shared_ptr<Tcp_connection>(new Tcp_connection(io_service));
}

asio::ip::tcp::socket& Tcp_connection::get_socket()
{
    return socket;
}

void Tcp_connection::start()
{
    // Read the person's id
    uint32_t pid = read_uint();

    // Read the other person's id
    uint32_t apid = read_uint();

    // Get the current relations and calculate the path
    Graph::graph_t relations = Fetcher::get_instance()->get_relations();
    Searcher searcher(relations);
    boost::shared_ptr<Graph::path_t> path =
        searcher.find_shortest_path(pid, apid, depth_limit);

    uint32_t path_length = !path ? 0 : path->size();

    // Write the path length
    write_uint(path_length);

    // Write the path
    for (uint32_t i = 0; i < path_length; i++)
        write_uint(path->at(i));
}

Tcp_connection::Tcp_connection(asio::io_service& io_service)
    : socket(io_service),
      depth_limit(Options::get_instance()->get_depth_limit())
{
}

uint32_t Tcp_connection::read_uint()
{
    asio::error_code error;
    uint32_t uint;
    socket.read_some(asio::buffer((void*) &uint, sizeof(uint)), error);
    if (error)
        throw asio::system_error(error);
    return uint;
}

void Tcp_connection::write_uint(uint32_t uint)
{
    asio::error_code error;
    socket.write_some(asio::buffer((void*) &uint, sizeof(uint)), error);
    if (error)
        throw asio::system_error(error);
}
