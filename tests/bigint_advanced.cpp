#define BOOST_TEST_MODULE BigInt class
#include <boost/test/included/unit_test.hpp>
#include "../src/bigint.cpp"
#include "../src/exceptions.h"

const t_bint MERSENNE_PRIMES[] =
{ 2, 3, 5, 7, 13, 17, 19, 31, 61, 89, 107, 127, 521, 607, 1279, 2203, 2281,
  3217, 4253, 4423, 9689, 9941, 11213, 19937, 21701, 23209, 44497, 86243,
  110503, 132049, 216091, 756839, 859433, 1257787, 1398269, 2976221, 3021377,
  6972593, 13466917, 20996011, 24036583, 25964951, 0 };
const t_bint PRIMES[] =
{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
  73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149,
  151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227,
  229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307,
  311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389,
  397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467,
  479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571,
  577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653,
  659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751,
  757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853,
  857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947,
  953, 967, 971, 977, 983, 991, 997, 0 };

using namespace bigint;

BOOST_AUTO_TEST_SUITE(ModularArighmetics)

BOOST_AUTO_TEST_CASE(PowerMod) {
    BigInt x;
    BigInt y;
    BigInt n;

    x = 0;
    y.generate();
    n = 0;
    BOOST_CHECK_THROW(x.powMod(y,n),DBZException);
    BOOST_CHECK_EQUAL(x, 0);
    BOOST_CHECK_EQUAL(n, 0);

    x = 0;
    y = 0;
    n = 0;
    BOOST_CHECK_THROW(x.powMod(y,n),DBZException);
    BOOST_CHECK_EQUAL(x, 0);
    BOOST_CHECK_EQUAL(y, 0);
    BOOST_CHECK_EQUAL(n, 0);

    x.generate();
    y.generate();
    n = 0;
    if (x == 0) {
        x++;
    }
    if (y == 0) {
        y++;
    }
    BOOST_CHECK_THROW(x.powMod(y,n),DBZException);
    BOOST_CHECK_EQUAL(n, 0);

    x = 0;
    y.generate();
    n.generate();
    if (y == 0) {
        y++;
    }
    if (n < 2) {
        n = 2;
    }
    x.powMod(y,n);
    BOOST_CHECK_EQUAL(x,0);

    x = 0;
    y = 0;
    n.generate();
    if (n < 2) {
        n = 2;
    }
    BOOST_CHECK_THROW(x.powMod(y,n),URException);
    BOOST_CHECK_EQUAL(x, 0);
    BOOST_CHECK_EQUAL(y, 0);

    x = 1;
    y.generate();
    n.generate();
    x.powMod(y,n);
    BOOST_CHECK_EQUAL(x,1);

    x.generate();
    y = 0;
    n.generate();
    x.powMod(y,n);
    BOOST_CHECK_EQUAL(x,1);

    x.generate();
    y.generate();
    n = 1;
    x.powMod(y,n);
    BOOST_CHECK_EQUAL(x,0);

    x = 2;
    y = 2;
    n = 5;
    x.powMod(y,n);
    BOOST_CHECK_EQUAL(x,4);

    x.generate();
    if (x + 1 == 0 ) {
        x--;
    }
    y = 1;
    n = x + 1;
    BigInt oldX(x);
    x.powMod(y,n);
    BOOST_CHECK_EQUAL(x,oldX);
    BOOST_CHECK_EQUAL(y,1);
    BOOST_CHECK_EQUAL(n,oldX + 1);
}

int monitorPowMod(BigInt* x, BigInt& y, BigInt& n) {
    x->powMod(y,n);
    return 0;
}

BOOST_AUTO_TEST_CASE(PowerMod_primes) {
    BigInt x;
    BigInt y;
    BigInt n;

    n = 17;
    y = n - 1;
    x.generate();
    if (x % n == 0 || n % x == 0) {
        x++;
    }
    BOOST_CHECK_NE(x % n,0);
    BOOST_CHECK_NE(n % x,0);
    x.powMod(y,n);
    BOOST_CHECK_EQUAL(x,1);

    n = 1;
    n <<= 7;
    n--;
    y = n - 1;
    x.generate();
    if (x % n == 0 || n % x == 0) {
        x++;
    }
    BOOST_CHECK_NE(x % n,0);
    BOOST_CHECK_NE(n % x,0);
    x.powMod(y,n);
    BOOST_CHECK_EQUAL(x,1);

    n = 1;
    t_bint prime = 1;
    for (t_size i = 0;
         MERSENNE_PRIMES[i] > 0 && MERSENNE_PRIMES[i] < NUMBER_CAPACITY; i++) {
        prime = MERSENNE_PRIMES[i];
    }
    n <<= prime;
    n--;
    y = n - 1;
    x.generate();
    if (x % n == 0 || n % x == 0) {
        x++;
    }
    BOOST_CHECK_NE(x % n,0);
    BOOST_CHECK_NE(n % x,0);

    boost::execution_monitor theMonitor;
    theMonitor.p_timeout.set(1);
    theMonitor.execute(boost::bind(monitorPowMod,&x,y,n));
    BOOST_CHECK_EQUAL(x,1);
}

BOOST_AUTO_TEST_SUITE_END()