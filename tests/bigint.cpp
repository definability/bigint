#define BOOST_TEST_MODULE BigInt class
#include <boost/test/included/unit_test.hpp>
#include "../src/bigint.cpp"

using namespace bigint;


BOOST_AUTO_TEST_SUITE(Constructor)

BOOST_AUTO_TEST_CASE(Comparison_with_word) {
    BigInt bi(1);
    BOOST_CHECK(bi==1);
    BOOST_CHECK(bi<=1);
    BOOST_CHECK(bi>=1);
    BOOST_CHECK(bi!=(t_bint)0);
    BOOST_CHECK(bi>=(t_bint)0);
    BOOST_CHECK(bi>(t_bint)0);
    BOOST_CHECK(bi!=2);
    BOOST_CHECK(bi<=2);
    BOOST_CHECK(bi<2);
    BOOST_CHECK(bi<-1);
    BOOST_CHECK(bi<=-1);

    BigInt a;
    BOOST_CHECK(a==0);
    BOOST_CHECK(a<=0);
    BOOST_CHECK(a>=0);
    BOOST_CHECK(a<1);
    BOOST_CHECK(a<=1);
    BOOST_CHECK(a<-1);
    BOOST_CHECK(a<=-1);
}

BOOST_AUTO_TEST_CASE(Comparison_with_BigInt) {
    BigInt bi(1);
    BigInt a;
    BigInt b(2);
    BigInt c(1);
    BigInt n(-1);
    BOOST_CHECK(bi==c);
    BOOST_CHECK(bi<=c);
    BOOST_CHECK(bi>=c);
    BOOST_CHECK(bi!=b);
    BOOST_CHECK(bi<=b);
    BOOST_CHECK(bi<b);
    BOOST_CHECK(bi!=a);
    BOOST_CHECK(bi>=a);
    BOOST_CHECK(bi>a);

    BOOST_CHECK(bi<n);
    BOOST_CHECK(bi<=n);
}


BOOST_AUTO_TEST_CASE(BOOST_comparison) {
    BigInt bi(1);
    BOOST_CHECK_EQUAL(bi,1);
    BOOST_CHECK_LE(bi,1);
    BOOST_CHECK_GE(bi,1);

    BOOST_CHECK_LT(bi,2);
    BOOST_CHECK_GT(bi,0);

    BOOST_CHECK_NE(bi,0);
    BOOST_CHECK_NE(bi,2);
}


BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE(Basic_functionality)



BOOST_AUTO_TEST_CASE(Equate_BigInt_word) {
    BigInt bi;
    t_bint a=0;
    bi=a;
    BOOST_CHECK_EQUAL(bi,a);
    a=1;
    bi=a;
    BOOST_CHECK_EQUAL(bi,a);
    t_bint b=0;
    bi=b;
    BOOST_CHECK_EQUAL(bi,b);
    b=1;
    BOOST_CHECK_MESSAGE(bi!=b, "Link copy detection (operator= properly work)");
}

BOOST_AUTO_TEST_CASE(Equate_BigInt_BigInt) {
    BigInt bi;
    BigInt a=0;
    bi=a;
    BOOST_CHECK_EQUAL(bi,a);
    a=1;
    bi=a;
    BOOST_CHECK_EQUAL(bi,a);
    BigInt b=0;
    bi=b;
    BOOST_CHECK_EQUAL(bi,b);
    b=1;
    BOOST_CHECK_MESSAGE(bi!=b, "Link copy detection (operator= properly work)");
}

BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE(Basic_arithmetics)


BOOST_AUTO_TEST_CASE(Test_negation) {
    BigInt a;
    BigInt b=~a;
    BOOST_CHECK_NE(a,b);
    b=~b;
    BOOST_CHECK_EQUAL(a,b);
    a=~a;
    BOOST_CHECK_NE(a,b);
    b=~b;
    BOOST_CHECK_EQUAL(a,b);
}

BOOST_AUTO_TEST_CASE(Increment_Decrement) {
    BigInt bi;
    BOOST_CHECK_EQUAL(bi,0);
    bi++;
    BOOST_CHECK_EQUAL(bi,1);
    bi++;
    BOOST_CHECK_EQUAL(bi,2);
    bi--;
    BOOST_CHECK_EQUAL(bi,1);
}

BOOST_AUTO_TEST_SUITE_END()
