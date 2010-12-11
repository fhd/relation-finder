relation-finder
===============

A daemon that finds the shortest path between two people in a social
network.

relation-finder listens for incoming network connections asking for
the shortest path between two people and calculates it based
relationship data regularly fetched from a social network's database.

Building
--------

This is what you'll need in order to build relation-finder yourself:

* Boost (at least version 1.42). In particular, the following
  libraries:
  * Boost.Asio
  * Boost.Assignment
  * Boost.Foreach
  * Boost.Filesystem
  * Boost.Program_options
  * Boost.Thread
  * Boost.Test

* The PostgreSQL C++ library (pqxx) (at least version 2.6)

* CMake (at least version 2.6)

On a Debian system, the required packages are:

* libboost-dev
* libboost-filesystem-dev
* libboost-program-options-dev
* libboost-thread-dev
* libboost-test-dev
* libasio-dev
* libpqxx-dev
* cmake

Once you've made sure that everything is in place, type:

    mkdir build
    cd build
    cmake ..
    make

After the build process is finished, the desired binary
(relation-finder) resides in *build*.

Running
-------

You'll need a properly set up PostgreSQL database; to get one with
some test data, execute *doc/setup_db.sql*.

After building relation-finder, you have two programs:

* relation-finder - the relation finding daemon
* relation-finder-client - a simple client documenting
  relation-finder's protocol

What you'll want to do is run *relation-finder*. To see how it's used,
execute:

    relation-finder --help

You'll have to set at least the database connection parameters.

If you want to see if it's working properly, use
*relation-finder-client*.

To run relation-finder, the libraries listed in the Compiling section
are required. Their headers, Boost.Test and Boost.Build are not.

On a Debian system, the packages are:

* libboost-thread
* libboost-program-options
* libboost-filesystem
* libpqxx

Installing
----------

To install relation-finder to */usr/local*, just execute the following command:

    make install

To install it to a different directory, execute:

    CMAKE_INSTALL_PREFIX=/some/path cmake ..
    make install

License
-------

Copyright (C) 2009 Felix H. Dahlke

This is open source software, licensed under the MIT license. See the
file COPYING for details.
