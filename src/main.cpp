#include <iostream>
#include <boost/thread.hpp>
#include <boost/thread/xtime.hpp>
#include <asio.hpp>
#include "options.hpp"
#include "util.hpp"
#include "fetcher.hpp"
#include "tcp_server.hpp"

/// A thread functor, updating the relations
class Fetcher_thread {
public:
    Fetcher_thread(const unsigned int& fetch_interval)
    {
        this->fetch_interval = fetch_interval;
    }

    void operator()()
    {
        boost::shared_ptr<Fetcher> f = Fetcher::get_instance();
        for (;;) {
            // Fetch new relations
            f->fetch();

            // Sleep for a while
            boost::xtime xt;
            boost::xtime_get(&xt, boost::TIME_UTC);
            xt.sec += fetch_interval;
            boost::thread::sleep(xt);
        }
    }

private:
    unsigned int fetch_interval;
};

int main(int argc, char* argv[])
{
    try {
        // Parse the commandline options
        boost::shared_ptr<Options> opts = Options::get_instance();
        try {
            opts->parse(argc, argv);
        } catch (int e) {
            return e;
        }

        Util::message("Initialised.");

        // Start the fetcher thread
        Fetcher_thread fetcher(opts->get_fetching_interval());
        boost::thread thread(fetcher);

        // Start the server and listen for incoming connections
        asio::io_service io_service;
        Tcp_server server(io_service, opts->get_port());
        io_service.run();
    } catch (std::exception& e) {
        std::cerr << "Caught an exception: " << e.what() << std::endl;
    }

    return 0;
}
