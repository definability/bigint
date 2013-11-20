#include "config.h"
#include "base.h"
#include "boolean.h"
#include "arithmetics.h"
#include "div.h"

    /**
      * Fast division of two numbers with equal sizes
      */
/*
    void fDiv(t_bint* a, t_bint* b, t_bint* remainder=NULL,
            t_size size=BLOCKS_NUMBER, t_size sizeR=0) {
            */
    void fDiv(t_bint* a, t_bint* b, t_bint* remainder, t_size size, t_size sizeR) {
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
            /*
            shr(b,2,size);
            shl(a,1,size);
            shl(b,1,size);
            */
            fDiv(a,b,NULL,new_size);
            cerr<<"</greater>"<<endl;
            return;
        }
        /*
        t_float divider=1/(2.0*(1<<(sizeof(t_bint)-1)));
        t_float u=a[size-1]+a[size-2]*divider;
        t_float v=b[size-1]+b[size-2]*divider;
        */
        t_float divider=(2.0*(1<<(sizeof(t_bint)-1)));
        t_float u=a[size-1]+a[size-2]/divider;
        t_float v=b[size-1]+b[size-2]/divider;
        t_float fResult=u/v;
        t_bint iResult=(t_bint)fResult;
        setNull(a,size);
        a[0]=iResult;
        cerr<<"</eqdiv>"<<endl;
    }

    /**
      * Fast division of big integer by word
      */
/*
    void fDiv(t_bint* a, t_bint b, t_bint* remainder=NULL,
            t_size size=BLOCKS_NUMBER, t_size sizeR=0) {
            */
    void fDiv(t_bint* a, t_bint b, t_bint* remainder, t_size size, t_size sizeR) {
        if (sizeR==0 && remainder!=NULL) sizeR=1;
    }


/*
    void divSS(t_bint* a, t_bint *b, t_bint* remainder=NULL,
            t_size sizeA=BLOCKS_NUMBER, t_bint sizeB=0, t_size sizeR=0) {
            */
    void divSS(t_bint* a, t_bint *b, t_bint* remainder, t_size sizeA, t_bint sizeB, t_size sizeR) {
        if (!sizeB) sizeB=sizeA;
        if (sizeR==0 && remainder!=NULL) sizeR=sizeB;
    }


    /**
      * Divide a by b. Keep result (quotient) in a.
      */
/*
    void mod(t_bint* a, t_bint* b, t_size sizeA=BLOCKS_NUMBER, t_size sizeB=0,
            t_bint* quotient=NULL, t_size sizeQ=0) {
            */
    void mod(t_bint* a, t_bint* b, t_size sizeA, t_size sizeB, t_bint* quotient, t_size sizeQ) {
        if (!sizeB) sizeB=sizeA;
        if (quotient!=NULL && sizeQ>0) setNull(quotient, sizeQ);
        int cmpResult=cmp(a,b,sizeA,sizeB);
        t_size n, m;
        /*
        t_size n=msw(b,sizeB)+1;
        t_size m=msw(a,sizeA)+1-n;
        */
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
                /*
                else if (m==0) {
                    //fDiv(a, b, remainder, sizeA, n);
                }
                else if (n==1) {
                    //fDiv(a, b[0], remainder, n+m);
                }*/
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


                    /*
                    t_size sizeD = mswA+2;
                    t_size sizeDt = mswA+2;
                    t_bint* divider = new t_bint[sizeD];
                    t_bint* divident = new t_bint[sizeDt];
                    shl(a,(BLOCK_SIZE-(n+m-BLOCK_SIZE)%BLOCK_SIZE)%BLOCK_SIZE,sizeA);
                    shl(b,(BLOCK_SIZE-(n-BLOCK_SIZE)%BLOCK_SIZE)%BLOCK_SIZE,sizeB);
                    setNull(divider,sizeD);
                    mov(divider,b,sizeB);
                    swl(divider,mswA-mswB,sizeD);

                    setNull(divident,sizeDt);
                    mov(divident,a,mswA+1);

                    for (t_size i=0; i<=m; i++) {
                    //while (m>=0) {
                        tmp_cmp = cmp(divident,divider,sizeDt,sizeD);
                        tmp = (bool)(tmp_cmp & (CMP_EQUAL|CMP_GREATER));
                        cerr<<endl;
                        displayBI(divident,sizeDt);
                        cerr<<":";
                        displayBI(divider,sizeD);
                        cerr<<endl;
                        if (tmp) {
                            sub(divident,divider,sizeDt,sizeD);
                        }
                        shl(divident,1,sizeDt);
                        if (quotient!=NULL && sizeQ>0) {
                            shl(quotient,1,sizeQ);
                            quotient[0]|=tmp;
                        }
                    //    m--;
                    }
                    if (!tmp) cerr<<"NOTMP"<<endl;
                    else cerr<<"YTMP"<<endl;
                    cerr<<"MSB: "<<msb(divident,sizeDt)
                        <<"; "<<msb(divident,sizeD);
                    shr(divident,m+1,sizeDt);
                    setNull(a,sizeA);
                    mov(a,divident,sizeDt);
                    */
                    cerr<<"</mod>"<<endl;
                }
                break;
            default:
                // Something's gone bad
                cerr<<"Unknown cmp result reached!"<<cmpResult<<endl;
                break;
        }
    }

/*
    void div(t_bint* a, t_bint* b, t_size sizeA=BLOCKS_NUMBER, t_size sizeB=0) {
    */
    void div(t_bint* a, t_bint* b, t_size sizeA, t_size sizeB) {
        if (!sizeB || sizeB>sizeA) sizeB=sizeA;
        t_size sizeQ=sizeA;
        t_bint* quotient = new t_bint[sizeQ];
        mod(a,b,sizeA,sizeB,quotient,sizeQ);
        setNull(a,sizeA);
        mov(a,quotient,sizeQ);
    }
