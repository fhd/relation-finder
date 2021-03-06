#include <iostream>
#include <boost/thread.hpp>
#include <boost/thread/xtime.hpp>
#include <asio.hpp>
#include "options.hpp"
#include "logger.hpp"
#include "fetcher.hpp"
#include "tcp_server.hpp"

/// A thread functor, updating the relations
class Fetcher_thread {
public:
    Fetcher_thread(Fetcher& fetcher, unsigned int fetch_interval)
        : fetcher(fetcher), fetch_interval(fetch_interval)
    {
    }

    void operator()()
    {
        for (;;) {
            // Fetch new relations
            fetcher.fetch();

            // Sleep for a while
            boost::xtime xt;
            boost::xtime_get(&xt, boost::TIME_UTC);
            xt.sec += fetch_interval;
            boost::thread::sleep(xt);
        }
    }

private:
    Fetcher& fetcher;
    unsigned int fetch_interval;
};

int main(int argc, char* argv[])
{
    try {
        // Parse the commandline options
        Options options(argc, argv);
        Logger::verbose = options.get_verbose();

        Logger::log("Initialised.");

        // Start the fetcher thread
        Fetcher fetcher(options);
        boost::thread thread(Fetcher_thread(fetcher,
                                            options.get_fetching_interval()));

        // Start the server and listen for incoming connections
        asio::io_service io_service;
        Tcp_server server(io_service, options.get_port(), fetcher,
                          options.get_depth_limit());
        io_service.run();
    } catch (int e) {
        return e;
    } catch (std::exception& e) {
        std::cerr << "Caught an exception: " << e.what() << std::endl;
    }

    return 0;
}
