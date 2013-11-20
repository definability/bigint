#include "config.h"
#include "base.h"
#include "boolean.h"
#include "mul.h"
#include "div.h"

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
