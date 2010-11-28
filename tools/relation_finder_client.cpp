/*
 * This is an example client for relation-finder, demonstrating its protocol
 * using Boost.Asio for network communication.
 *
 * The protocol is pretty simple, the only data send is a couple of unsigned
 * 32-bit integers. It basically works like this:
 * 1. Connect to relation-finder via TCP.
 * 2. Send the user ID of the first person (user A).
 * 3. Send the user ID of the second person (user B).
 * 4. Read the length of path. If that number is 0, no path could be found.
 * 5. Read as many user IDs as the path was long.
 *    This is the result, the path from user A to user B.
 */

#include <string>
#include <iostream>
#include <boost/array.hpp>
#include <asio.hpp>

using asio::ip::tcp;

uint32_t read_uint(tcp::socket& socket)
{
    asio::error_code error;
    uint32_t uint;
    socket.read_some(asio::buffer((void*) &uint, sizeof(uint)), error);
    if (error)
        throw asio::system_error(error);
    return uint;
}

void write_uint(tcp::socket& socket, uint32_t uint)
{
    asio::error_code error;
    socket.write_some(asio::buffer((void*) &uint, sizeof(uint)), error);
    if (error)
        throw asio::system_error(error);
}

int main(int argc, char* argv[])
{
    // Read address and request parameters from the commandline
    if (argc < 5) {
        std::cerr << "relation-finder-client - asks relation-finder for a "
                  << "connection between two people" << std::endl
                  << "Usage: relation-finder-client HOST PORT PERSON1 PERSON2"
                  << std::endl;
        return 1;
    }

    std::string host = argv[1];
    std::string port = argv[2];
    unsigned int pid1 = atoi(argv[3]);
    unsigned int pid2 = atoi(argv[4]);

    try {
        // Resolve the host
        asio::io_service io_service;
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(host, port);
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        tcp::resolver::iterator end;

        // Connect to the server
        tcp::socket socket(io_service);
        asio::error_code error = asio::error::host_not_found;
        while (error && endpoint_iterator != end) {
            socket.close();
            socket.connect(*endpoint_iterator++, error);
        }
        if (error)
            throw asio::system_error(error);

        // Write the person's id
        write_uint(socket, pid1);

        // Write the other person's id
        write_uint(socket, pid2);

        // Read the length of the path
        int path_length = read_uint(socket);
        if (path_length == 0) {
            std::cout << "No path was found." << std::endl;
        } else {
            std::cout << "Found a path: ";

            // Read the path
            for (int i = 0; i < path_length; i++) {
                unsigned int node = read_uint(socket);
                std::cout << node;
                if (i != path_length - 1)
                    std::cout << " -> ";
            }
            std::cout << std::endl;
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
