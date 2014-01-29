#include "config.h"
#include "base.h"
#include "boolean.h"
#include "mul.h"
#include "div.h"
#include "exceptions.h"
#include "barrett.h"
#include "modular.h"

void pow_mod(t_bint* a,
             t_bint* b,
             t_bint* n,
             t_size sizeA,
             t_size sizeB,
             t_size sizeN) {
    if (!sizeB || sizeB > sizeA) {
        sizeB = sizeA;
    }
    if (!sizeN) {
        sizeN = sizeA;
    }

    t_size mswN = msw(n,sizeN) + 1;
    t_size sizeMu = mswN * 2 + 1;
    t_bint* mu = new t_bint[sizeMu];
    setNull(mu,sizeMu);
    mu[sizeMu - 1] = 1;
    barrettMu(mu, n, sizeMu, sizeN);

    mod(a,n,sizeA,sizeN);
    barrettMod(a, n, mu, sizeA, sizeN, sizeMu);

    if (isNull(a,sizeA) && isNull(b,sizeB)) {
        throw URException();
    }
    else if (isNull(a,sizeA) || cmp(a,1,sizeA) == CMP_EQUAL) {
    }
    else if (isNull(b,sizeB)) {
        setNull(a,sizeA);
        a[0] = 1;
        return;
    }
    else {
        t_size sizeT = sizeN * 2;
        t_size sizeR = sizeN * 2;
        t_bint* tmp = new t_bint[sizeT];
        t_bint* result = new t_bint[sizeR];
        t_size sizeP = sizeB;
        t_bint* p = new t_bint[sizeP];

        setNull(p,sizeP);
        setNull(tmp,sizeT);
        setNull(result,sizeR);

        result[0] = 1;
        mov(p,b,sizeP);
        mov(tmp,a,sizeA);

        t_bint i = 0;
        while (!isNull(p,sizeP)) {
            if (p[0] & 1) {
                //mulMod(result,tmp,n,sizeR,sizeT,sizeN);
                barrettMulMod(result,tmp,n,mu,sizeR,sizeT,sizeN,sizeMu);
            }

            sqrMod(tmp,n,sizeT,sizeN);
            //barrettSqrMod(tmp, n, mu, sizeT, sizeN, sizeMu);

            if (isNull(tmp,sizeT)) {
                break;
            }
            else if(cmp(tmp,1,sizeT) == CMP_EQUAL) {
                break;
            }
            shr(p,1,sizeP);
            i++;
        }
        mov(a,result,sizeA);
        mod(a,n,sizeA,sizeN);
        //barrettMod(a, n, mu, sizeA, sizeN, sizeMu);

        delete[] tmp;
        delete[] result;
        delete[] p;
        delete[] mu;
    }
}

void mulMod(t_bint* a,
            t_bint* b,
            t_bint* n,
            t_size sizeA,
            t_size sizeB,
            t_size sizeN) {
    mod(a,n,sizeA,sizeN);
    mul(a,b,sizeA,sizeB);
    mod(a,n,sizeA,sizeN);
}

void sqrMod(t_bint* a, t_bint* n, t_size sizeA, t_size sizeN) {
    sqr(a,sizeA);
    mod(a,n,sizeA,sizeN);
}

void barrettMulMod(t_bint* a,
                   t_bint* b,
                   t_bint* n,
                   t_bint* mu,
                   t_size sizeA,
                   t_size sizeB,
                   t_size sizeN,
                   t_size sizeMu) {
    barrettMod(a,n,mu,sizeA,sizeN,sizeMu);
    mul(a,b,sizeA,sizeB);
    barrettMod(a,n,mu,sizeA,sizeN,sizeMu);
}

void barrettSqrMod(t_bint* a, t_bint* n, t_bint* mu, t_size sizeA,
                   t_size sizeN, t_size sizeMu) {
    sqr(a,sizeA);
    barrettMod(a, n, mu, sizeA, sizeN, sizeMu);
}
