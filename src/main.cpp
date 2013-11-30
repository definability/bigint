#include <iostream>
#include "bigint.cpp"
//#include "bigint.h"

using namespace std;

int main() {
    cerr<<"<xml>"<<endl;
    bigint::BigInt bi_a(0x06);
    bigint::BigInt bi_b(0x94);
    bigint::BigInt bi_n(0x94);
    cout<<"print 'Python test started.'"<<endl;
    for (t_size i=0; i<10; i++) {
        bi_a.generate();
        /*
        bi_b=(t_bint)1;
        bi_b<<=BLOCK_SIZE;
        bi_b+=3;
        */
        /*
        bi_b=(t_bint)126;
        bi_n=(t_bint)127;
        */
        /*
        bi_b.generate();
        bi_n.generate();
        bi_b>>=(1<<7);
        bi_b>>=5;
        //bi_n>>=(1<<7);
        bi_a=(t_bint)2;
        bi_n=(t_bint)17;
        cout<<"a="<<bi_a<<endl;
        cout<<"b="<<bi_b<<endl;
        cout<<"n="<<bi_n<<endl;
        cout<<"print '"<<bi_a<<", "<<bi_b<<", "<<bi_n<<"'"<<endl;
        //cout<<"print 'Result is "<<bi_a.modPower(bi_b, bi_n)<<"'"<<endl;
        cerr<<"PRELUDE"<<endl;
        bi_a.modPower(bi_b, bi_n);
        cerr<<"DONE"<<endl;
        cout<<"print 'Result is "<<bi_a<<"'"<<endl;
        cout<<"result="<<bi_a<<"==(a**b)%n"<<endl;
        cout<<"print result"<<endl;
        cout<<"if not result:"<<endl;
        cout<<"    print 'Right answer is', (a**b)%n"<<endl;
        cout<<"print ''"<<endl;
        */
    }
    /*
    for (t_size i=0; i<3; i++) {
        bi_a.generate();
        bi_b.generate();
        bi_n.generate();
        cout<<"print '"<<bi_a<<", "<<bi_b<<", "<<bi_n<<"'"<<endl;
        cout<<"print 'Result is "<<bi_a.modPower(bi_b, bi_n)<<"'"<<endl;
    }
    */
    for (t_size i=0; i<100; i++) {
        bi_a.generate();
        cout<<"a="<<bi_a<<endl;
        cout<<"print a>>1==";
        bi_a>>=1;
        cout<<bi_a<<endl;
        cout<<"print 'Difference is',(a>>1)-"<<bi_a<<endl;
        cout<<"print a>>1"<<endl;
        cout<<"print ''"<<endl;
    }
    /*
    //DIVISION
    for (t_size i=0; i<100; i++) {
        bi_a.generate();
        bi_b.generate();
        bi_b>>=0;
        cout<<"a="<<bi_a<<endl;
        cout<<"b="<<bi_b<<endl;
        cout<<"print 'MSW: "<<bi_a.MSB()<<", "<<bi_b.MSB()<<"'"<<endl;
        cout<<"print ";
        cout<<"("<<bi_a<<"%"<<bi_b<<")%(3**0x"<<NUMBER_CAPACITY<<")==";
        bi_a%=bi_b;
        cout<<bi_a<<endl;
        cout<<"print '%x'%a"<<endl;
        cout<<"print '%x'%b"<<endl;
        cout<<"print 'Difference is',"<<endl;
        cout<<"print hex(a%b-"<<hex<<bi_a<<")"<<endl;
        cout<<"print 'My result is "<<hex<<bi_a<<"'"<<endl;
        cout<<"print 'a%b=',hex(a%b)"<<endl;
        //cout<<"print 'Test value is',hex("<<dec<<BLOCK_MAX_VALUE<<"-int(hex(b)[2:-0x"<<BLOCKS_NUMBER*2*8-2*8+1<<"],16))"<<endl;
        cout<<"print ''"<<endl;
    }
    */
    /*
    // SQUARE
    for (t_size i=0; i<500; i++) {
        bi_a.generate();
        cout<<"a="<<bi_a<<endl;
        cout<<"print ";
        cout<<"("<<bi_a<<"*"<<bi_a<<")%(2**0x"<<NUMBER_CAPACITY<<")==";
        bi_a*=bi_a;
        cout<<bi_a<<endl;
        cout<<"print 'Difference is',"<<endl;
        cout<<"print hex((a*a)%(2**0x"<<NUMBER_CAPACITY<<")-"<<bi_a<<")"<<endl;
    }
    */
    /*
    //MULTIPLICATION
    for (t_size i=0; i<500; i++) {
        bi_a.generate();
        bi_b.generate();
        cout<<"a="<<bi_a<<endl;
        cout<<"b="<<bi_b<<endl;
        cout<<"print ";
        cout<<"("<<bi_a<<"*"<<bi_b<<")%(2**0x"<<NUMBER_CAPACITY<<")==";
        bi_a*=bi_b;
        cout<<bi_a<<endl;
        cout<<"print 'Difference is',"<<endl;
        cout<<"print hex((a*b)%(2**0x"<<NUMBER_CAPACITY<<")-"<<bi_a<<")"<<endl;
    }
    */

    /*
    cout<<"print 'Python test started. a="<<bi_a<<", b="<<bi_b<<"'"<<endl;
    for (t_size i=0;i<6;i++) {
        cout<<"a="<<bi_a<<endl;
        cout<<"b="<<bi_b<<endl;
        cout<<"print ";
        cout<<bi_a<<"*"<<bi_b<<"==";
        bi_a*=bi_b;
        cout<<bi_a<<endl;
        cout<<"print 'Difference is',"<<endl;
        cout<<"print hex(a*b-"<<bi_a<<")"<<endl;
        cout<<"a="<<bi_a<<endl;
        cout<<"b="<<bi_b<<endl;
        cout<<"print ";
        cout<<bi_a<<"*"<<bi_b<<"==";
        bi_b*=bi_a;
        cout<<bi_b<<endl;
        cout<<"print 'Difference is',"<<endl;
        cout<<"print hex(a*b-"<<bi_b<<")"<<endl;
    }
    */
    cerr<<"</xml>"<<endl;
    return 0;
}
