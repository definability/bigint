#define BOOST_TEST_MODULE BigInt class basics
#include <boost/test/included/unit_test.hpp>
#include <boost/utility/binary.hpp>
#include "../src/bigint.cpp"

using namespace bigint;


BOOST_AUTO_TEST_SUITE(Constructor)

BOOST_AUTO_TEST_CASE(Comparison_with_word) {
    BigInt bi(1);
    BOOST_CHECK(bi==1);
    BOOST_CHECK(bi<=1);
    BOOST_CHECK(bi>=1);
    BOOST_CHECK(bi!=0);
    BOOST_CHECK(bi>=0);
    BOOST_CHECK(bi>0);
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
    BOOST_CHECK_MESSAGE(bi!=b, "Link copy detection (correctness of operator=)");
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
    BOOST_CHECK_MESSAGE(bi!=b, "Link copy detection (correctness of operator=)");
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(Binary_arithmetics)

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

BOOST_AUTO_TEST_CASE(Test_AND) {
    BigInt a=BOOST_BINARY(0001);
    a&=BOOST_BINARY(0001);
    BOOST_CHECK_EQUAL(a,BOOST_BINARY(0001));
    BigInt b=BOOST_BINARY(0101);
    b=a&BOOST_BINARY(0001);
    BOOST_CHECK_EQUAL(a,b);
    b=a&BOOST_BINARY(0001);
    BOOST_CHECK_EQUAL(a,b);
    a=a&BOOST_BINARY(0010);
    BOOST_CHECK_EQUAL(a,BOOST_BINARY(0000));
    b&=-1;
    BOOST_CHECK_EQUAL(b,BOOST_BINARY(0001));
}

BOOST_AUTO_TEST_CASE(Test_OR) {
    BigInt a=BOOST_BINARY(0001);
    a|=BOOST_BINARY(0010);
    BOOST_CHECK_EQUAL(a,BOOST_BINARY(0011));
    BigInt b=BOOST_BINARY(0101);
    a=b|BOOST_BINARY(0001);
    BOOST_CHECK_EQUAL(a,BOOST_BINARY(0101));
    b=a|BOOST_BINARY(0001);
    BOOST_CHECK_EQUAL(a,b);
    a=a|BOOST_BINARY(0010);
    BOOST_CHECK_EQUAL(a,BOOST_BINARY(0111));
    b|=-1;
    BOOST_CHECK_EQUAL(b,-1);
}

BOOST_AUTO_TEST_CASE(Test_XOR) {
    BigInt a=BOOST_BINARY(0001);
    BigInt b=BOOST_BINARY(0101);
    BigInt oldA(a);
    BigInt oldB(b);
    a^=b;
    b=a^b;
    BOOST_CHECK_EQUAL(b,oldA);
    a=a^b;
    BOOST_CHECK_EQUAL(a,oldB);
    a^=a;
    BOOST_CHECK_EQUAL(a,0);
    b=b^b;
    BOOST_CHECK_EQUAL(b,0);
}

BOOST_AUTO_TEST_CASE(Test_SHR) {
    BigInt a=BOOST_BINARY(1000);
    a>>=1;
    BOOST_CHECK_EQUAL(a,BOOST_BINARY(0100));
    BigInt b=BOOST_BINARY(1010);
    b>>=1;
    BOOST_CHECK_EQUAL(b,BOOST_BINARY(0101));
    b=a>>2;
    BOOST_CHECK_EQUAL(b,BOOST_BINARY(0001));
    a=a>>1;
    BOOST_CHECK_EQUAL(a,BOOST_BINARY(0010));
    b=b>>5;
    BOOST_CHECK_EQUAL(b,0);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(Basic_arithmetics)

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


