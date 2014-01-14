#include "config.h"
#include "base.h"
#include "boolean.h"
#include "arithmetics.h"
#include "mul.h"
#include "div.h"
#include "barrett.h"

void barrettMu(t_bint* b, t_bint* n, t_size sizeB, t_size sizeN) {
    div(b, n, sizeB, sizeN);
}

void barrettMod(t_bint* a, t_bint* n, t_bint* mu,
        t_size sizeA, t_size sizeN, t_size sizeMu) {
    t_size sizeQ = sizeA;
    t_size k = msw(n,sizeN)+1;
    if (k-1>msw(a,sizeA)) return;
    t_bint* q = new t_bint[sizeQ];
    mov(q, a, sizeA);
    swr(q,k,sizeQ);
    mul(q,mu,sizeQ,sizeMu);
    swr(q,k,sizeQ);
    /*
    cerr<<"BEFORE: a=";
    displayBI(a,sizeA);
    cerr<<endl;
    */
    mul(q,n,sizeQ,sizeN);
    setNull(&a[k],sizeA-k);
    /*
    cerr<<"AFTER: a=";
    displayBI(a,sizeA);
    cerr<<endl;
    */
    setNull(&q[k],sizeQ-k);
    switch (cmp(a,q,sizeA,sizeQ)) {
        case CMP_EQUAL:
            setNull(a,sizeA);
            break;
        case CMP_LOWER:
            a[k]=1;
        case CMP_GREATER:
            sub(a,q,sizeA,sizeQ);
            break;
    }
    int i=0;
    /*
    while(cmp(a,n,sizeA,sizeN)==CMP_GREATER) {
        if (i>1000) {
            cerr<<"Big loop! i="<<i<<endl;
            cerr<<"a=";
            displayBI(a,sizeA);
            cerr<<endl;
            cerr<<"n=";
            displayBI(n,sizeN);
            cerr<<endl<<endl;
        }
        sub(a,n,sizeA,sizeN);
        i++;
    }
    if (i>2)
        cerr<<i<<" minuses"<<endl;
        */
    mod(a,n,sizeA,sizeN);
}
