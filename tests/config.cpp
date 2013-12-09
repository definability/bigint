#define BOOST_TEST_MODULE Config test
#include <boost/test/included/unit_test.hpp>
#include "../src/config.h"

BOOST_AUTO_TEST_CASE(config) {
        BOOST_CHECK_GT(((t_bint)BLOCK_MAX_BIT),0);
        BOOST_CHECK_GT(((t_bint)BLOCK_MAX_VALUE),0);
        BOOST_WARN_EQUAL((t_bint)(BLOCK_MAX_VALUE + 1),0);
}