#include "config.h"
#include "base.h"
#include "boolean.h"
#include "mul.h"
#include "div.h"

void pow_mod(t_bint* a, t_bint* b, t_bint* n, t_size sizeA, t_size sizeB, t_size sizeN) {
    if (!sizeB || sizeB>sizeA) sizeB=sizeA;
    if (!sizeN) sizeN=sizeA;

    if (isNull(a,sizeA)) {
        return;
    }
    if (cmp(a,1,sizeA)==CMP_EQUAL) {
        return;
    }
    if (isNull(b,sizeB)) {
        a[0]=1;
        return;
    }

    mod(a,n,sizeA,sizeN);

    if (isNull(a,sizeA)) {
        return;
    }
    else if (cmp(a,1,sizeA)==CMP_EQUAL) {
        return;
    }
    else {
        t_size sizeT = sizeN*2;
        t_size sizeR = sizeN*2;
        t_bint* tmp = new t_bint[sizeT];
        t_bint* result = new t_bint[sizeR];
        t_size sizeP = sizeB;
        t_bint* p = new t_bint[sizeP];

        setNull(p,sizeP);
        setNull(tmp,sizeT);
        setNull(result,sizeR);

        result[0]=1;
        mov(p,b,sizeP);
        mov(tmp,a,sizeA);

        t_bint i=0;
        while (!isNull(p,sizeP)) {
            if (p[0]&1) {
                mul(result,tmp,sizeR,sizeT);
                mod(result,n,sizeR,sizeN);
            }
            mul(tmp,tmp,sizeT);
            mod(tmp,n,sizeT,sizeN);
            if (isNull(tmp,sizeT)) {
                break;
            }
            else if(cmp(tmp,1,sizeT)==CMP_EQUAL) {
                break;
            }
            shr(p,1,sizeP);
            i++;
        }
        mov(a,result,sizeA);
        mod(a,n,sizeA,sizeN);

        delete[] tmp;
        delete[] result;
        delete[] p;
    }
}
