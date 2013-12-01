#define BOOST_TEST_MODULE BigInt class
#include <boost/test/included/unit_test.hpp>
#include <boost/utility/binary.hpp>
#include "../src/bigint.cpp"
#include "../src/exceptions.h"

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

BOOST_AUTO_TEST_CASE(Equate_random_BigInt) {
    BigInt bi;
    BigInt a;
    a.generate();
    bi=a;
    BOOST_CHECK_EQUAL(bi,a);
    a.generate();
    bi=a;
    BOOST_CHECK_EQUAL(bi,a);
    BigInt b=0;
    bi=b;
    BOOST_CHECK_EQUAL(bi,b);
    b.generate();
    if (b==0) {
        b=1;
    }
    BOOST_CHECK_MESSAGE(bi!=b, "Link copy detection (correctness of operator=)");
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(Binary_arithmetics)

BOOST_AUTO_TEST_CASE(Negation) {
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

BOOST_AUTO_TEST_CASE(AND) {
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

BOOST_AUTO_TEST_CASE(AND_random) {
    BigInt a;
    BigInt b;
    a.generate();
    BigInt c(a);
    c&=a;
    BOOST_CHECK_EQUAL(a,c);
    a=a&a.MAX_VALUE();
    BOOST_CHECK_EQUAL(a,c);
    if (a==0) {
        a=a&1;
    }
    else {
        a=a&0;
    }
    BOOST_CHECK_EQUAL(a,0);
    c=b;
    b&=b;
    BOOST_CHECK_EQUAL(b,c);
    c=c&c;
    BOOST_CHECK_EQUAL(c,c);
    b&=0;
    BOOST_CHECK_EQUAL(b,0);
}

BOOST_AUTO_TEST_CASE(OR) {
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

BOOST_AUTO_TEST_CASE(TEST_OR_random) {
    BigInt a;
    BigInt b;
    a.generate();
    b.generate();
    BigInt c(a);
    c|=a;
    BOOST_CHECK_EQUAL(a,c);
    a=a|0;
    BOOST_CHECK_EQUAL(a,c);
    a=c|c.MAX_VALUE();
    BOOST_CHECK_EQUAL(a,c.MAX_VALUE());
    c=b;
    b|=b;
    BOOST_CHECK_EQUAL(b,c);
    c=c|c;
    BOOST_CHECK_EQUAL(c,c);
    b|=b.MAX_VALUE();
    BOOST_CHECK_EQUAL(b,b.MAX_VALUE());

}

BOOST_AUTO_TEST_CASE(XOR) {
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

BOOST_AUTO_TEST_CASE(XOR_random) {
    BigInt a;
    BigInt b;
    a.generate();
    b.generate();
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

BOOST_AUTO_TEST_CASE(SHR) {
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


BOOST_AUTO_TEST_CASE(SHR_random) {
    BigInt a;
    a.generate();
    if (a==0) {
        a.generate();
        if (a==0) {
            a=BLOCK_MAX_VALUE;
        }
    }
    a>>=1;
    BOOST_CHECK_NE(a,0);
    a>>=NUMBER_CAPACITY;
    BOOST_CHECK_EQUAL(a,0);
}

BOOST_AUTO_TEST_CASE(SHL) {
    BigInt a=BOOST_BINARY(0001);
    a<<=1;
    BOOST_CHECK_EQUAL(a,BOOST_BINARY(0010));
    BigInt b=BOOST_BINARY(1010);
    b<<=1;
    BOOST_CHECK_EQUAL(b,BOOST_BINARY(10100));
    b=a<<2;
    BOOST_CHECK_EQUAL(b,BOOST_BINARY(1000));
    a=a<<1;
    BOOST_CHECK_EQUAL(a,BOOST_BINARY(0100));
}

BOOST_AUTO_TEST_CASE(SHL_random) {
    BigInt a(1);
    a<<=NUMBER_CAPACITY-1;
    BOOST_CHECK_NE(a,0);
    a=a<<1;
    BOOST_CHECK_EQUAL(a,0);
    a=2;
    a=a<<NUMBER_CAPACITY-2;
    BOOST_CHECK_NE(a,0);
    a<<=1;
    BOOST_CHECK_EQUAL(a,0);
}

BOOST_AUTO_TEST_CASE(SHL_SHR_random) {
    const t_size TEST_SHIFT=NUMBER_CAPACITY/2;
    BigInt a;
    BigInt b;
    BigInt c;
    a.generate();

    // For test correctness
    b=1;
    b<<=NUMBER_CAPACITY-1;
    b|=1;
    a|=b;

    c=a;
    BOOST_CHECK_EQUAL(c,a);
    b=a<<TEST_SHIFT;
    b=b>>(NUMBER_CAPACITY-TEST_SHIFT);
    a>>=TEST_SHIFT;
    a=a<<TEST_SHIFT;
    BOOST_CHECK_NE(c,a);
    BOOST_CHECK_NE(c,b);
    BOOST_CHECK_EQUAL(c,a|b);
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

BOOST_AUTO_TEST_CASE(Increment_Decrement_random) {
    BigInt bi;
    BigInt tmp;
    bi.generate();
    tmp=bi;
    bi++;
    BOOST_CHECK_NE(bi,tmp);
    bi--;
    BOOST_CHECK_EQUAL(bi,tmp);
    tmp--;
    tmp--;
    bi--;
    BOOST_CHECK_NE(bi,tmp);
    tmp++;
    BOOST_CHECK_EQUAL(bi,tmp);
    bi=BLOCK_MAX_VALUE;
    bi++;
    BOOST_CHECK_EQUAL(bi>>(BLOCK_SIZE),1);
    BOOST_CHECK_EQUAL(bi&BLOCK_MAX_VALUE,0);
    bi--;
    BOOST_CHECK_EQUAL(bi,BLOCK_MAX_VALUE);
    bi=bi.MAX_VALUE();
    bi++;
    BOOST_CHECK_EQUAL(bi,0);
    bi--;
    BOOST_CHECK_EQUAL(bi,bi.MAX_VALUE());
}

BOOST_AUTO_TEST_CASE(Plus) {
    BigInt a;
    BigInt b(a+1);
    a++;
    BOOST_REQUIRE_EQUAL(a,b);
    a=0;
    a+=10;
    BOOST_CHECK_EQUAL(a,10);
    b=a+4;
    BOOST_CHECK_EQUAL(b,14);
    BOOST_CHECK_EQUAL(a,10);
    b=a+8;
    BOOST_CHECK_EQUAL(b,18);
    a=a+b+a;
    BOOST_CHECK_EQUAL(a,38);
    b=a;
    a+=0;
    BOOST_CHECK_EQUAL(a,b);
    b=b+0;
    BOOST_CHECK_EQUAL(a,b);
}

BOOST_AUTO_TEST_CASE(Minus) {
    BigInt a;
    BigInt b(a-1);
    a--;
    BOOST_REQUIRE_EQUAL(a,b);
    a=100;
    a-=10;
    BOOST_CHECK_EQUAL(a,90);
    b=a-4;
    BOOST_CHECK_EQUAL(b,86);
    BOOST_CHECK_EQUAL(a,90);
    b=a-8;
    BOOST_CHECK_EQUAL(b,82);
    b-=80;
    BOOST_CHECK_EQUAL(b,2);
    a=a-b-b-b;
    BOOST_CHECK_EQUAL(a,84);
    a-=a;
    b=b-b;
    BOOST_CHECK_EQUAL(a,0);
    BOOST_CHECK_EQUAL(b,0);
    b=a;
    a-=0;
    BOOST_CHECK_EQUAL(a,b);
    b=b-0;
    BOOST_CHECK_EQUAL(a,b);

}

BOOST_AUTO_TEST_CASE(Plus_Minus_random) {
    BigInt a;
    BigInt b;
    a.generate();
    b.generate();
    if (a<b) {
        a^=b;
        b^=a;
        a^=b;
    }
    BigInt oldA(a);
    a++;
    BOOST_REQUIRE_EQUAL(a,oldA+1);
    a--;
    BOOST_REQUIRE_EQUAL(a,oldA);
    BigInt oldB(b);
    b--;
    BOOST_REQUIRE_EQUAL(b,oldB-1);
    b++;
    BOOST_REQUIRE_EQUAL(b,oldB);
    a-=b;
    a=b+a;
    BOOST_CHECK_EQUAL(a,oldA);
    a=a-b;
    a+=b;
    BOOST_CHECK_EQUAL(a,oldA);
    a+=0;
    BOOST_CHECK_EQUAL(a,oldA);
    b=b+0;
    BOOST_CHECK_EQUAL(b,oldB);
    a=b+0;
    BOOST_CHECK_EQUAL(a,b);
    BOOST_CHECK_EQUAL(a,oldB);
}

BOOST_AUTO_TEST_CASE(Multiply) {
    BigInt a;
    a*=5;
    BOOST_CHECK_EQUAL(a,0);
    a=a*7;
    BOOST_CHECK_EQUAL(a,0);
    a=10;
    a=a*2;
    BOOST_CHECK_EQUAL(a,20);
    a*=3;
    BOOST_CHECK_EQUAL(a*2,120);
    BOOST_CHECK_EQUAL(a,60);
    a*=1;
    BOOST_CHECK_EQUAL(a,60);
    a=a*1;
    BOOST_CHECK_EQUAL(a,60);
    a*=0;
    BOOST_CHECK_EQUAL(a,0);
    a=50;
    BOOST_CHECK_EQUAL(a*0,0);
    BOOST_CHECK_EQUAL(a,50);
    a=a*0;
    BOOST_CHECK_EQUAL(a,0);
}


BOOST_AUTO_TEST_CASE(Divide) {
    BigInt a;
    a/=5;
    BOOST_CHECK_EQUAL(a,0);
    a=a/5;
    BOOST_CHECK_EQUAL(a,0);
    a=100;
    a/=2;
    BOOST_CHECK_EQUAL(a,50);
    BOOST_CHECK_EQUAL(a/11,4);
    a=a/10;
    BOOST_CHECK_EQUAL(a,5);
    a/=a;
    BOOST_CHECK_EQUAL(a,1);
    a=200;
    a=a/a;
    BOOST_CHECK_EQUAL(a,1);
    BOOST_CHECK_THROW(a/=0,DBZException);
    a=0;
    BOOST_CHECK_THROW(a/=0,DBZException);
    BigInt b;
    BOOST_CHECK_THROW(b/=a,DBZException);
    BOOST_CHECK_THROW(b/a,DBZException);
    BOOST_CHECK_THROW(a/0,DBZException);
    BOOST_CHECK_THROW(b/0,DBZException);
}

BOOST_AUTO_TEST_CASE(Modulus) {
    BigInt a;
    a=10;
    BOOST_CHECK_EQUAL(a%1,0);
    BOOST_CHECK_EQUAL(a%a,0);
    BOOST_CHECK_EQUAL(a%5,0);
    BOOST_CHECK_EQUAL(a%3,1);
    BigInt b;
    b=37;
    BOOST_CHECK_EQUAL(b%a,7);
}

BOOST_AUTO_TEST_CASE(Multiply_Divide_random) {
    BigInt a;
    a.generate();
    BOOST_CHECK_EQUAL(a*0,0);
    BOOST_CHECK_THROW(a/0,DBZException);
    BOOST_CHECK_EQUAL(a*2,a<<1);
    BOOST_CHECK_EQUAL(a*8,a<<3);
    BOOST_CHECK_EQUAL(a/2,a>>1);
    BOOST_CHECK_EQUAL(a/8,a>>3);
    BigInt b;
    BigInt c;
    if (BLOCKS_NUMBER>1) {
        b=BLOCK_MAX_VALUE;
        a=BLOCK_MAX_VALUE*b;
        BOOST_CHECK_NE(a,b);
        a/=BLOCK_MAX_VALUE;
        BOOST_CHECK_EQUAL(a,BLOCK_MAX_VALUE);
        BOOST_CHECK_EQUAL(BLOCK_MAX_VALUE/a,1);
    }
    if (BLOCKS_NUMBER>2) {
        c.generate();
        b=BLOCK_MAX_VALUE;
        a=b*b+c;
        BOOST_CHECK_EQUAL(a%BLOCK_MAX_VALUE,c%BLOCK_MAX_VALUE);
    }
    BOOST_CHECK_EQUAL(a%b,a-(a/b)*b);
    a.generate();
    b.generate();
    BOOST_CHECK_EQUAL(a%b,a-(a/b)*b);
    BOOST_CHECK_EQUAL(b%a,b-(b/a)*a);
}

BOOST_AUTO_TEST_SUITE_END()
