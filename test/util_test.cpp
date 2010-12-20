#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>

#include <util.hpp>

BOOST_AUTO_TEST_CASE(convert_int_to_string)
{
    BOOST_REQUIRE_EQUAL(Util::convert_to_string(15), "15");
}

BOOST_AUTO_TEST_CASE(convert_double_to_string)
{
    BOOST_REQUIRE_EQUAL(Util::convert_to_string(0.1), "0.1");
}

BOOST_AUTO_TEST_CASE(convert_char_to_string)
{
    BOOST_REQUIRE_EQUAL(Util::convert_to_string('a'), "a");
}
