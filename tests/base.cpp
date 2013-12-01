#define BOOST_TEST_MODULE Base functions test
#include <boost/test/included/unit_test.hpp>
#include "../src/bigint.cpp"

BOOST_AUTO_TEST_CASE(bigintConstructor) {
    using namespace bigint;
    BigInt* bi = new BigInt();
    BOOST_CHECK(bi==0);
}
