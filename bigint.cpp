#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include "config.h"
#include "base.h"
#include "boolean.h"
#include "mul.h"
#include "div.h"
#include "modular.h"
#include "bigint.h"

/*
typedef long t_size;

typedef unsigned long ULONG;
typedef unsigned long t_bint;
typedef signed long t_sbint;
typedef long double t_float;

//TODO: bits->bytes sizes
const unsigned long BLOCK_SIZE = 8*sizeof(t_bint); //64;
const unsigned long NUMBER_CAPACITY = (long)1<<8;
const unsigned long BLOCKS_NUMBER = NUMBER_CAPACITY/BLOCK_SIZE;
const unsigned long ULONG_SIZE = sizeof(ULONG);

const t_bint BLOCK_MAX_VALUE = 0xFFFFFFFFFFFFFFFF;
const t_bint BLOCK_MAX_BIT = (long)1<<(BLOCK_SIZE-1);
*/

using namespace std;

namespace random32 {

    int Mersenne_32(int x, int i) {
        return 1812433253 * (x ^ (x >> 30)) + i;
    }
    
    int x=time(NULL);
    int i=0;

    int rand32() {
        x=Mersenne_32(x,i);
        i++;
        return x;
    }

}

namespace bigint {

    // TODO: provide this enum
    enum CmpResult { EQUAL, GREATER, LOWER };

    /*
    const unsigned char CMP_EQUAL = 0;
    const unsigned char CMP_GREATER = 1;
    const unsigned char CMP_LOWER = 2;
    */

    void displayBI(t_bint* a, t_size size=BLOCKS_NUMBER) {
        cerr<<"0x"<<hex;
        for (; a[size-1]==0; size--);
        for (; size>0;size--)
            cerr<<setfill('0')<<setw(2)<<(unsigned long long)a[size-1];
    }

    void scanBI(t_bint* a, const char* aStr, t_size sizeA=BLOCKS_NUMBER) {
        t_size size=strlen(aStr);
        t_size loopEnd=size-BLOCKS_NUMBER*BLOCK_SIZE;
        loopEnd=loopEnd>0?loopEnd:0+size%ULONG_SIZE;
        t_size i;
        char* currentNumber=new char[ULONG_SIZE*2+1];
        currentNumber[ULONG_SIZE*2]=0;
        char* tmp;
        for (i=size-ULONG_SIZE;i>=loopEnd;i-=ULONG_SIZE, (ULONG*)a++) {
            memcpy(currentNumber, &aStr[i], ULONG_SIZE);
            *(ULONG*)a=strtoul(currentNumber, &tmp, 16);
        }
        memcpy(currentNumber, &aStr[loopEnd-size%ULONG_SIZE], ULONG_SIZE);
        *(ULONG*)a=strtoul(currentNumber, &tmp, 16);
    }

    void generateBI(t_bint* a, t_size sizeA=BLOCKS_NUMBER) {
        t_size i;
        t_size size=sizeA*BLOCK_SIZE/(8*sizeof(int));
        int* tmp=(int*)a;
        for (i=0; i<size; i++) {
            *tmp=random32::rand32();
            tmp++;
        }
    }

    /*
    unsigned char cmp(t_bint* a, t_bint b, t_size size=BLOCKS_NUMBER) {
        if (a[0]>b) return CMP_GREATER;
        for (t_size i=1; i<size; i++) {
            if (a[i])
                return CMP_GREATER;
        }
        if (a[0]==b) return CMP_EQUAL;
        if (a[0]<b) return CMP_LOWER;
    }

    unsigned char cmp(t_bint* a, t_bint* b,
            t_size size1 = BLOCKS_NUMBER, t_size size2 = 0) {
        if (!size2) size2=size1;
        t_size i;
        if (size1>size2) {
            for (i=size1-1; i>=size2; i--) {
                if (a[i])
                    return CMP_GREATER;
            }
        }
        else if (size2>size1) {
            for (i=size2-1; i>=size1; i--) {
                if (b[i])
                    return CMP_LOWER;
            }
        }
        else
            i=size1-1;
        for (; i>=0; i--) {
            if (a[i]>b[i])
                return CMP_GREATER;
            else if (a[i]<b[i])
                return CMP_LOWER;
        }
        return CMP_EQUAL;
    }

    void mov(t_bint* a, t_bint* b, t_size size=BLOCKS_NUMBER) {
        for (t_size i=0; i<size; i++)
            a[i]=b[i];
    }

    t_size msw(t_bint* a, t_size size=BLOCKS_NUMBER) {
        while (--size>=0) {
            if (a[size]>0)
                return size;
        }
        cerr<<"<size>BLANK</size>"<<endl;
        return -1;
    }

    t_size msb(t_bint* a, t_size size=BLOCKS_NUMBER) {
        t_size result = msw(a,size);
        t_size i;
        if (result==-1)
            return -1;
        t_bint tmp=a[result];
        result*=BLOCK_SIZE;
        for (i=0; i<BLOCK_SIZE; i++) {
            tmp>>=1;
            if (!tmp)
                return result+i;
        }
        return -2;
    }

    bool isNull(t_bint* a, t_size size=BLOCKS_NUMBER) {
        if (!a || !size)
            return true;
        while (size-->0) {
            if (a[size])
                return false;
        }
        return true;
    }

    void setNull(t_bint* a, t_size size=BLOCKS_NUMBER) {
        while (size-->0) {
            a[size]=0;
        }
    }
    */

    /*
    void swl(t_bint *a, t_size shift, t_size size=BLOCKS_NUMBER) {
        if (shift>=size)
            setNull(a,size);
        else if (shift>0) {
            t_size i;
            for (i=size-1; i>=shift; i--)
                a[i]=a[i-shift];
            for (i=0; i<shift; i++)
                a[i]=0;
        }
    }

    void swr(t_bint *a, t_size shift, t_size size=BLOCKS_NUMBER) {
        if (shift>=size)
            setNull(a,size);
        else if (shift>0) {
            t_size i;
            for (i=0; i<size-shift-1; i++)
                a[i]=a[i+shift];
            for (i=size-shift; i<size; i++)
                a[i]=0;
        }
    }

    void shl(t_bint* a, t_size shift, t_size size=BLOCKS_NUMBER) {
        cerr<<"<shift>"<<endl;
        if (shift==0) {
        }
        else if (shift>=size*BLOCK_SIZE) {
            cerr<<"Shift set null"<<endl;
            setNull(a,size);
        }
        else if (shift<BLOCK_SIZE) {
            t_bint tmp1=0, tmp2=0;
            for (t_size i=0; i<size; i++) {
                tmp2 = a[i] >> (BLOCK_SIZE-shift);
                a[i] <<= shift;
                a[i] |= tmp1;
                tmp1 = tmp2;
            }
        }
        else if (shift%BLOCK_SIZE == 0) {
            t_size i, blockShift=shift/BLOCK_SIZE;
            cerr<<"size="<<size<<endl;
            cerr<<"blockShift="<<blockShift<<endl;
            for (i=size-1; i>=blockShift; i--) {
                a[i]=a[i-blockShift];
                cerr<<"a["<<i<<"]=a["<<i-blockShift<<"]"
                    <<"="<<(int)a[i]<<endl;
            }
            for (i=0; i<blockShift; i++)
                a[i]=0;
        }
        else {
            shl(a,shift-shift%BLOCK_SIZE,size);
            shl(a,shift%BLOCK_SIZE,size);
        }
        cerr<<"</shift>"<<endl;
    }

    void shr(t_bint* a, t_size shift, t_size size=BLOCKS_NUMBER) {
        cerr<<"<shift>"<<endl;
        if (shift==0) {
        }
        else if (shift>=size*BLOCK_SIZE) {
            setNull(a,size);
        }
        else if (shift<BLOCK_SIZE) {
            t_bint tmp1=0, tmp2=0;
            for (t_size i=size-1; i>=0; i--) {
                tmp2 = a[i] << (BLOCK_SIZE-shift);
                a[i] >>= shift;
                a[i] |= tmp1;
                tmp1 = tmp2;
            }
        }
        else if (shift%BLOCK_SIZE == 0) {
            t_size blockShift=shift/BLOCK_SIZE;
            for (t_size i=0; i<size-blockShift; i++) {
                a[i]=a[i+blockShift];
            }
            for (t_size i=size-blockShift; i<BLOCKS_NUMBER; i++)
                a[i]=0;
        }
        else {
            shr(a,shift%BLOCK_SIZE);
            shr(a,shift-shift%BLOCK_SIZE);
        }
        cerr<<"</shift>"<<endl;
        return;
    }
    */

    /*
    unsigned char getCarry(t_bint a, t_bint b, t_bint result) {
        return ( (a&b) | (b|a) & (~result) ) >> (BLOCK_SIZE-1);
    }

    void add(t_bint* a, t_bint* b, 
            t_size size1 = BLOCKS_NUMBER, t_size size2 = 0) {
        if (!size2 || size2>size1) size2=size1;
        t_bint carry=0;
        t_bint tmp_value, i;
        for (i=0; i<size2; i++) {
            tmp_value=a[i];
            a[i]+=b[i]+carry;
            carry=getCarry(tmp_value,b[i],a[i]);
        }
        if (carry && size2<size1) {
            for (i=size2; i<size1; i++) {
                a[i]+=1;
                if (a[i]) break;
            }
        }
    }

    void negate(t_bint* a, t_size size=BLOCKS_NUMBER) {
        t_size i;
        for (i=0; i<size; i++) {
            a[i]=~a[i];
            if (~a[i]) {
                a[i]++;
                break;
            }
        }
        i++;
        for (; i<size; i++)
            a[i]=~a[i];
    }

    void sub(t_bint* a, t_bint* b, 
            t_size size1 = BLOCKS_NUMBER, t_size size2 = 0) {
        if (!size2 || size2>size1) size2=size1;
        unsigned char carry=0;
        t_bint tmp;
        t_size i;
        for (i=0; i<size2; i++) {
            tmp=a[i];
            a[i]-=b[i]+carry;
            carry=getCarry(a[i],b[i],tmp);
        }
        if (carry) {
            for (i=size2; i<size1; i++) {
                a[i]-=1;
                if (a[i]!=-1)
                    break;
            }
        }
    }
    */

    /**
      * Karatsuba's multiplication method (a=a*b).
      * That's why parameter `a' must have the resulting length.
      */
    /*
    void mul(t_bint* a, t_bint* b, 
            t_size sizeA = BLOCKS_NUMBER, t_size sizeB = 0) {
        if (!sizeB || sizeB>sizeA) sizeB=sizeA;
        if (isNull(a, sizeA) || isNull(b, sizeB)) {
            setNull(a, sizeA);
        }
        else if (sizeA==1) {
            a[0]*=b[0];
        }
        else {
            t_size mswA=msw(a,sizeA), mswB=msw(b,sizeB);
            if ((mswA|mswB)==0) {
                // 20-30% productivity increase
                asm (
                        "mul %3"
                        : "=a" (a[0]), "=d" (a[1])
                        : "a" (a[0]), "d" (b[0])
                    );
            }
            else {
                mswA++;
                mswB++;
                t_size n, i;
                n=(mswA>mswB?mswA:mswB);
                n=n/2+n%2;
                t_size sizeR=4*n;
                t_size sizeX0=n<mswA?n:mswA, sizeX1=mswA>sizeX0?mswA-sizeX0:0,
                       sizeY0=n<mswB?n:mswB, sizeY1=mswB>sizeY0?mswB-sizeY0:0;
                t_bint **x=new t_bint*[1+(bool)sizeX1],
                       **y=new t_bint*[1+(bool)sizeY1],
                       *tmp=new t_bint[sizeR],
                       *result=new t_bint[sizeR];
                //n*=BLOCK_SIZE;
                // Initialize X0, X1
                x[0]=new t_bint[sizeX0];
                for (i=0;i<sizeX0;i++)
                    x[0][i]=a[i];
                if (sizeX1) {
                    x[1]=new t_bint[sizeX1];
                    for (i=0;i<sizeX1;i++)
                        x[1][i]=a[i+sizeX0];
                }
                // Initialize Y0, Y1
                y[0]=new t_bint[sizeY0];
                for (i=0;i<sizeY0;i++)
                    y[0][i]=b[i];
                if (sizeY1) {
                    y[1]=new t_bint[sizeY1];
                    for (i=0;i<sizeY1;i++)
                        y[1][i]=b[i+sizeY0];
                }
                
                // Formula: X1*Y1*(2^2n+2^n)+(X1-X0)(Y0-Y1)*b^n+X0*Y0*(b^n+1)
                // STAGES:
                // Init: result<-0, tmp<-0
                // First: X1*Y1*(2^2n+2^n)=X1*Y1*2^n*(2^n+1)=X1*Y1*2^n*(2^n+1)
                // tmp<-(X1*Y1)<<n, result<-tmp<<n+tmp
                // Second: X0*Y0*(2^n+1)
                // tmp<-X0*Y0, result<-result+tmp<<n+tmp
                // Third: (X1-X0)(Y0-Y1)*2^n
                // minus if (X1>X0 and Y0>Y1) or (X1<X0 and Y0<Y1) =>
                // => minux <- -1 if (X1>X0)^(Y1>Y0) else 1
                // tmp=abs(X1-X0)*abs(Y0-Y1)*minus
                // result<-result+tmp

                setNull(result,sizeR);
                setNull(tmp,sizeR);
                // STAGE1
                if (!isNull(x[1],sizeX1) && !isNull(y[1],sizeY1)) {
                    mov(tmp,x[1],sizeX1);
                    mul(tmp,y[1],sizeR,sizeY1);
                    mov(result,tmp,sizeR);
                    swl(result,n,sizeR);
                    setNull(tmp,sizeR);
                }
                // STAGE2
                if (!isNull(x[0],sizeX0) && !isNull(x[0],sizeY0)) {
                    mov(tmp,x[0],sizeX0);
                    mul(tmp,y[0],sizeR,sizeY0);
                    add(result,tmp,sizeR,sizeR);
                    setNull(tmp,sizeR);
                }
                mov(tmp,result,sizeR);
                swl(result,n,sizeR);
                add(result,tmp,sizeR);
                setNull(tmp,sizeR);
                // STAGE3
                unsigned char cmpX0X1, cmpY0Y1;
                if (!sizeX1)
                    cmpX0X1=CMP_GREATER;
                else
                    cmpX0X1=cmp(x[0],x[1],sizeX0,sizeX1);
                if (!sizeY1)
                    cmpY0Y1=CMP_GREATER;
                else
                    cmpY0Y1=cmp(y[0],y[1],sizeY0,sizeY1);
                if (cmpX0X1!=CMP_EQUAL && cmpY0Y1!=CMP_EQUAL) {
                    if (cmpX0X1==CMP_LOWER) {
                        sub(x[1],x[0],sizeX1, sizeX0);
                        mov(x[0],x[1],sizeX1);
                        sizeX0=sizeX1;
                    }
                    else if (cmpX0X1==CMP_GREATER && sizeX1!=0)
                        sub(x[0],x[1],sizeX0, sizeX1);
                    if (cmpY0Y1==CMP_GREATER && sizeY1!=0)
                        sub(y[0],y[1],sizeY0, sizeY1);
                    else if (cmpY0Y1==CMP_LOWER) {
                        sub(y[1],y[0],sizeY1, sizeY0);
                        mov(y[0],y[1],sizeY1);
                        sizeY0=sizeY1;
                    }
                    mov(tmp,x[0],sizeX0);
                    mul(tmp,y[0],sizeR,sizeY0);
                    swl(tmp,n,sizeR);
                    if ((cmpX0X1==CMP_GREATER) ^ (cmpY0Y1==CMP_LOWER))
                        sub(result,tmp,sizeR,sizeR);
                    else
                        add(result,tmp,sizeR,sizeR);
                }
                setNull(a,sizeA);
                mov(a,result,sizeR<sizeA?sizeR:sizeA);
                delete[] tmp;
            }
        }
    }
    */


    /**
      * Fast division of two numbers with equal sizes
      */
    /*
    void fDiv(t_bint* a, t_bint* b, t_bint* remainder=NULL,
            t_size size=BLOCKS_NUMBER, t_size sizeR=0) {
        if (sizeR==0 && remainder!=NULL) sizeR=size;
        cerr<<"<eqdiv>"<<endl;
        if (BLOCK_MAX_VALUE-b[size-1]>((t_bint)1<<(BLOCK_SIZE-1))) {
            cerr<<"<greater>"<<endl;
            cerr<<hex<<((t_bint)1<<(BLOCK_SIZE-1))<<endl;
            cerr<<"Size="<<size<<endl;
            t_size new_size=size;
            if (size>5) {
                swr(a,1,size);
                swr(b,1,size);
                new_size--;
            }
            shl(a,1,size);
            shl(b,1,size);
            fDiv(a,b,NULL,new_size);
            cerr<<"</greater>"<<endl;
            return;
        }
        t_float divider=(2.0*(1<<(sizeof(t_bint)-1)));
        t_float u=a[size-1]+a[size-2]/divider;
        t_float v=b[size-1]+b[size-2]/divider;
        t_float fResult=u/v;
        t_bint iResult=(t_bint)fResult;
        setNull(a,size);
        a[0]=iResult;
        cerr<<"</eqdiv>"<<endl;
    }
    */

    /**
      * Fast division of big integer by word
      */
        /*
    void fDiv(t_bint* a, t_bint b, t_bint* remainder=NULL,
            t_size size=BLOCKS_NUMBER, t_size sizeR=0) {
        if (sizeR==0 && remainder!=NULL) sizeR=1;
    }


    void divSS(t_bint* a, t_bint *b, t_bint* remainder=NULL,
            t_size sizeA=BLOCKS_NUMBER, t_bint sizeB=0, t_size sizeR=0) {
        if (!sizeB) sizeB=sizeA;
        if (sizeR==0 && remainder!=NULL) sizeR=sizeB;
    }
    */


    /**
      * Divide a by b. Keep result (quotient) in a.
      */
        /*
    void mod(t_bint* a, t_bint* b, t_size sizeA=BLOCKS_NUMBER, t_size sizeB=0,
            t_bint* quotient=NULL, t_size sizeQ=0) {
        if (!sizeB) sizeB=sizeA;
        if (quotient!=NULL && sizeQ>0) setNull(quotient, sizeQ);
        int cmpResult=cmp(a,b,sizeA,sizeB);
        t_size n, m;
        switch (cmpResult) {
            case CMP_LOWER:
                //setNull(a,sizeA);
                //mov(a,b,sizeB);
                break;
            case CMP_EQUAL:
                setNull(a,sizeA);
                if (quotient!=NULL && sizeQ>0) quotient[0]=1;
                break;
            case CMP_GREATER:
                n = msb(b, sizeB)+1;
                m = msb(a, sizeA)+1-n;
                if (sizeQ==0 && quotient!=NULL) sizeQ=n;
                if (n+m<BLOCKS_NUMBER) {
                    if (quotient!=NULL && sizeQ>0) quotient[0]=a[0]/b[0];
                    a[0]%=b[0];
                }
                else {
                    cerr<<"<mod>"<<endl;
                    t_size mswA = msw(a, sizeA);
                    t_size mswB = msw(b, sizeB);
                    t_size sizeD = mswA+2;
                    t_bint* divider = new t_bint[sizeD];
                    //t_bint* dt = new t_bint[sizeD];
                    setNull(divider,sizeD);
                    mov(divider,b,sizeD);

                    cerr<<"LERROR"<<endl;
                    shl(divider,m,sizeD);

                    unsigned char tmp_cmp, tmp, shifted=0;

                    //for (t_size i=0; i<=m; i++) {
                    t_size i=m;
                    while (true) {
                        tmp_cmp = cmp(a,divider,sizeA,sizeD);
                        tmp = (bool)(tmp_cmp & (CMP_EQUAL|CMP_GREATER));
                        if (tmp) {
                            sub(a,divider,sizeA,sizeD);
                        }
                        if (quotient!=NULL && sizeQ>0) {
                            shl(quotient,1,sizeQ);
                            quotient[0]|=tmp;
                        }

                        i--;
                        //if (i==-1) break;
                        if (cmp(divider,b,sizeD,sizeB)==CMP_EQUAL) break;
                        shr(divider,1,sizeD);
                        //if (cmp(divider,b,sizeD,sizeB)==CMP_LOWER) break;
                    }
                    cerr<<"NO ERROR"<<endl;
                    while (cmp(a,divider,sizeA,sizeD)&(CMP_GREATER|CMP_EQUAL)) {
                        cerr<<"LOOP ERROR"<<endl;
                        sub(a,divider,sizeA,sizeD);
                    }
                        cerr<<"NO LOOP ERROR"<<endl;
                    delete[] divider;
                        cerr<<"DELETED"<<endl;
                    //}
                    cerr<<"</mod>"<<endl;
                }
                break;
            default:
                // Something's gone bad
                cerr<<"Unknown cmp result reached!"<<cmpResult<<endl;
                break;
        }
    }

    void div(t_bint* a, t_bint* b, t_size sizeA=BLOCKS_NUMBER, t_size sizeB=0) {
        if (!sizeB || sizeB>sizeA) sizeB=sizeA;
        t_size sizeQ=sizeA;
        t_bint* quotient = new t_bint[sizeQ];
        mod(a,b,sizeA,sizeB,quotient,sizeQ);
        setNull(a,sizeA);
        mov(a,quotient,sizeQ);
    }
    */

        /*
    void pow_mod(t_bint* a, t_bint* b, t_bint* n,
            t_size sizeA=BLOCKS_NUMBER, t_size sizeB=0, t_size sizeN=0) {
        if (!sizeB || sizeB>sizeA) sizeB=sizeA;
        if (!sizeN) sizeN=sizeA;
        t_size sizeT = sizeN*2;
        t_size sizeR = sizeT;
        t_bint* tmp = new t_bint[sizeT];
        t_bint* result = new t_bint[sizeR];
        t_size sizeP = msw(b,sizeB)+1;
        t_bint* p = new t_bint[sizeP];
        setNull(p,sizeP);
        setNull(tmp,sizeT);
        setNull(result,sizeR);
        result[0]=1;
        mod(a,n,sizeA,sizeN);
        mov(p,b,sizeP);
        if (isNull(a,sizeA)) return;
        mov(tmp,a,sizeN);
        while (!isNull(p,sizeP)) {
            if (p[0]&1) {
                mul(result,tmp,sizeR,sizeT);
                mod(result,n,sizeR,sizeN);
            }
            mul(tmp,tmp,sizeT);
            shr(p,1,sizeP);
        }
        mov(a,result,sizeA);
        mod(a,n,sizeA,sizeN);
        delete[] tmp;
        delete[] result;
    }
    */

    class BigInt {
    private:
        t_bint* value;//[BLOCKS_NUMBER];

        void copy(const BigInt& source) {
            for (t_size i=0; i<BLOCKS_NUMBER; i++)
                this->value[i] = source[i];
        }

        void copy(t_bint source) {
            for (t_size i=1; i<BLOCKS_NUMBER; i++)
                this->value[i] = 0;
            this->value[0] = source;
        }

        void copy(t_sbint source) {
            if (source>0) {
                this->copy((t_bint)source);
            }
            else if (source==0) {
                this->setNull();
            }
            else {
                for (t_size i=1; i<BLOCKS_NUMBER; i++)
                    this->value[i] = BLOCK_MAX_VALUE;
                this->value[0] = (t_bint)source-1;
            }
        }

        void copy(t_bint* source, t_size size=BLOCKS_NUMBER) {
            this->setNull();
            for (t_size i=0; i<size; i++) {
                this->value[i]=source[i];
            }
        }

        void setNull() {
            for (t_size i=0; i<BLOCKS_NUMBER; i++)
                this->value[i] = 0;
        }
    public:
        BigInt() {
            this->value = new t_bint[BLOCKS_NUMBER];
        }

        BigInt(const BigInt& source) {
            this->value = new t_bint[BLOCKS_NUMBER];
            this->copy(source);
        }

        BigInt(t_bint source) {
            this->value = new t_bint[BLOCKS_NUMBER];
            this->copy(source);
        }

        BigInt(t_bint* source, t_size size=BLOCKS_NUMBER) {
            this->copy(source,size);
        }

        ~BigInt() {
            delete[] this->value;
        }

        BigInt& generate() {
            generateBI(this->value, BLOCKS_NUMBER);
            return *this;
        }

        t_size MSW() {
            return msw(this->value, BLOCKS_NUMBER);
        }

        t_size MSB() {
            return msb(this->value, BLOCKS_NUMBER);
        }

        BigInt& modPower(BigInt& p, BigInt& n) {
            pow_mod(this->value, p.value, n.value);
            return (*this);
        }

        const t_bint operator[] (t_size i) const {
            return this->value[i];
        }

        BigInt& operator=(t_bint source) {
            this->copy(source);
        }

        BigInt& operator=(const BigInt& source) {
            this->copy(source);
        }

        BigInt& operator=(t_sbint source) {
            this->copy(source);
        }

        BigInt& operator~() {
            for (int i=0; i<BLOCKS_NUMBER; i++)
                this->value[i]=~(this->value[i]);
            return (*this);
        }

        BigInt& operator>>=(t_size shift) {
            /*
            if (shift==0) {
                return *(this);
            }
            else if (shift>=NUMBER_CAPACITY) {
                this->setNull();
                return *(this);
            }
            else if (shift<BLOCK_SIZE) {
                t_bint tmp1=0, tmp2=0;
                for (t_size i=BLOCKS_NUMBER; i>0; --i) {
                    tmp2 = this->value[i] << (BLOCK_SIZE-shift);
                    this->value[i] >>= shift;
                    this->value[i] |= tmp1;
                    tmp1 = tmp2;
                }
                return *(this);
            }
            else if (shift%BLOCK_SIZE == 0) {
                for (t_size i=0; i<BLOCKS_NUMBER-shift; i++)
                    this->value[i]=this->value[i+shift];
                for (t_size i=BLOCKS_NUMBER-shift; i<BLOCKS_NUMBER; i++)
                    this->value[i]=0;
                return *(this);
            }
            else {
                (*this)>>=shift/BLOCK_SIZE;
                (*this)>>=shift%BLOCK_SIZE;
                return *(this);
            }
            */
            shr(this->value,shift);
            return *(this);
        }

        BigInt& operator<<=(t_size shift) {
            /*
            if (shift==0) {
                return *(this);
            }
            else if (shift>=NUMBER_CAPACITY) {
                this->setNull();
                return *(this);
            }
            else if (shift<BLOCK_SIZE) {
                t_bint tmp1=0, tmp2=0;
                for (t_size i=0; i<BLOCKS_NUMBER; i++) {
                    tmp2 = this->value[i] >> (BLOCK_SIZE-shift);
                    this->value[i] <<= shift;
                    this->value[i] |= tmp1;
                    tmp1 = tmp2;
                }
                return *(this);
            }
            else if (shift%BLOCK_SIZE == 0) {
                for (t_size i=BLOCKS_NUMBER; i>BLOCKS_NUMBER-shift; --i)
                    this->value[i]=this->value[i-shift];
                for (t_size i=0; i<=BLOCKS_NUMBER-shift; i++)
                    this->value[i]=0;
                return *(this);
            }
            else {
                (*this)<<=shift/BLOCK_SIZE;
                (*this)<<=shift%BLOCK_SIZE;
                return *(this);
            }
            */
            shl(this->value,shift,BLOCKS_NUMBER);
            return *(this);
        }

        BigInt& operator|=(const BigInt& operand) {
            for (t_size i=0; i<BLOCKS_NUMBER; i++)
                this->value[i]|=operand[i];
        }

        BigInt& operator&=(const BigInt& operand) {
            for (t_size i=0; i<BLOCKS_NUMBER; i++)
                this->value[i]&=operand[i];
        }

        BigInt& operator^=(const BigInt& operand) {
            for (t_size i=0; i<BLOCKS_NUMBER; i++)
                this->value[i]^=operand[i];
        }

        BigInt& operator+=(const BigInt& source) {
            unsigned char carry=0; //, tmp_carry=0;
            t_bint tmp_value;
            for (t_size i=0; i<BLOCKS_NUMBER; i++) {
                tmp_value=this->value[i];
                this->value[i]+=source[i]+carry;
                carry = ( (tmp_value&source[i]) | (source[i]|tmp_value) & (~this->value[i]) ) >> (BLOCK_SIZE-1);
                /*
                tmp_carry = (carry && (this->value[i]+source[i]==BLOCK_MAX_VALUE))\
                            || (this->value[i]+source[i]<this->value[i]);
                this->value[i]+=source[i]+carry;carry = tmp_carry;
                if (source[i]==0 && carry==0)
                    continue;
                else if (source[i]!=0 && carry==0) {
                    if (BLOCK_MAX_VALUE-this->value[i]<source[i]) {
                        this->value[i]=source[i]-(BLOCK_MAX_VALUE-this->value[i])-1;
                        carry = 1;
                    }
                    else
                        this->value[i]+=source[i];
                    continue;
                }
                else if (source[i]==0 && carry==1) {
                    if (this->value[i]==BLOCK_MAX_VALUE)
                        this->value[i]=0;
                    else {
                        this->value[i]++;
                        carry=0;
                    }
                    continue;
                }
                else {
                    if (BLOCK_MAX_VALUE-this->value[i]<source[i])
                        this->value[i]=source[i]-\
                                       (BLOCK_MAX_VALUE-this->value[i]);
                    else if (this->value[i]==0 && source[i]==BLOCK_MAX_VALUE)
                        this->value[i]=0;
                    else {
                        this->value[i]=source[i]+1;
                        carry=0;
                    }
                    continue;
                }
                */
            }
        }

        BigInt& operator+=(t_bint* source) {
            t_bint carry=0; //, tmp_carry=0;
            t_bint tmp_value;
            for (t_size i=0; i<BLOCKS_NUMBER; i++) {
                tmp_value=this->value[i];
                this->value[i]+=source[i]+carry;
            }
            return *this;
        }

        BigInt& operator-=(BigInt source) {
            (*this)+=~source;
            (*this)+=BigInt(1);
            return *this;
        }

        BigInt& operator*=(const BigInt& source) {
            // Karatsuba
            mul(this->value,source.value,BLOCKS_NUMBER);
            return *this;
        }

        BigInt& operator/=(const BigInt& source) {
            div(this->value,source.value);
            return *this;
        }

        BigInt& operator%=(const BigInt& source) {
            mod(this->value, source.value);
            return *this;
        }

        bool operator>=(const BigInt& source) {
            return cmp(this->value, source.value) & CMP_GREATER | CMP_EQUAL;
        }

        bool operator==(const BigInt& source) {
            return cmp(this->value, source.value) & CMP_EQUAL;
        }

        bool operator<=(const BigInt& source) {
            return cmp(this->value, source.value) & CMP_LOWER | CMP_EQUAL;
        }

        bool operator>(const BigInt& source) {
            return cmp(this->value, source.value) & CMP_GREATER;
        }

        bool operator<(const BigInt& source) {
            return cmp(this->value, source.value) & CMP_LOWER;
        }

        bool operator>=(const t_bint source) {
            return cmp(this->value, source) & CMP_GREATER | CMP_EQUAL;
        }

        bool operator==(const t_bint source) {
            return cmp(this->value, source) & CMP_EQUAL;
        }

        bool operator<=(const t_bint source) {
            return cmp(this->value, source) & CMP_LOWER | CMP_EQUAL;
        }

        bool operator>(const t_bint source) {
            return cmp(this->value, source) & CMP_GREATER;
        }

        bool operator<(const t_bint source) {
            return cmp(this->value, source) & CMP_LOWER;
        }


        friend ostream& operator<<(ostream& os, const BigInt& bi) {
            t_size i=BLOCKS_NUMBER;
            while (i-->1 && bi[i]==0);
            os<<"0x";
            os<<hex;
            if (i==0) {
                os<<(unsigned long long)bi[0];
                return os;
            }
            os<<(unsigned long long)bi[i];
            while (i-->0)
                os<<setfill('0')<<setw(BLOCK_SIZE/4)<<(unsigned long long)bi[i];
            return os;
        }

        friend istream& operator>>(istream& is, const BigInt& bi) {
            return is;
        }
    };

}
