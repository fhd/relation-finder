relation-finder
===============

A daemon that finds the shortest path between two people in a social
network.

relation-finder regularly fetches the relationships between people
from the database of a social networking site. It listens for incoming
network connections asking for the shortest path between two people
(via other people) and calculates it.

Building
--------

This is what you'll need in order to build relation-finder yourself:

Boost (at least version 1.34)
In particular, the following libraries:

* Boost.Asio
* Boost.Assignment
* Boost.Foreach
* Boost.Filesystem
* Boost.Program_options
* Boost.Thread
* Boost.Test

You will also need Boost.Build (AKA bjam).

The PostgreSQL C++ library (pqxx) (at least version 2.6)

On a Debian system, the required packages are:

* libboost-dev
* libboost-filesystem-dev
* libboost-program-options-dev
* libboost-thread-dev
* libboost-test-dev
* libasio-dev
* boost-build
* libpqxx-dev

Once you've made sure that everything is in place, type:

    bjam release

After the build process is finished, the desired binary
(relation-finder) resides in *dist/bin*.

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
- libboost-thread
- libboost-program-options
- libboost-filesystem
- libpqxx

Installing
----------

To install everything, just invoke the following command:

    bjam release -s DIST_DIR=/usr/local

To install just relation-finder (recommended), execute:

    bjam release relation-finder -s DIST_DIR=/usr/local

If you would like to remove it for some reason, invoke:

    bjam clean -s DIST_DIR=/usr/local

You can of course use whichever directory you like instead of */usr/local*.

License
-------

Copyright (C) 2009 Felix H. Dahlke

This is open source software, licensed under the MIT license. See the
file COPYING for details.
