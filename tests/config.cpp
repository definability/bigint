#define BOOST_TEST_MODULE Config test
#include <boost/test/included/unit_test.hpp>
#include "../src/config.h"

BOOST_AUTO_TEST_CASE(config) {
    BOOST_CHECK(((t_bint)BLOCK_MAX_BIT)>0);
    BOOST_CHECK(((t_bint)BLOCK_MAX_VALUE)>0);
}
