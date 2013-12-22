#include "config.h"
#include "base.h"
#include "boolean.h"
#include "arithmetics.h"
#include "div.h"

/**
 * Divide a by b. Keep result (reminder) in a.
 */
void mod(t_bint* a,
         t_bint* b,
         t_size sizeA,
         t_size sizeB,
         t_bint* quotient,
         t_size sizeQ) throw (DBZException) {
    if (isNull(b)) {
        throw DBZException();
    }
    if (!sizeB) {
        sizeB = sizeA;
    }
    if (quotient != NULL && sizeQ > 0) {
        setNull(quotient, sizeQ);
    }
    int cmpResult = cmp(a,b,sizeA,sizeB);
    t_size n, m;
    switch (cmpResult) {
    case CMP_LOWER:
        break;
    case CMP_EQUAL:
        setNull(a,sizeA);
        if (quotient != NULL && sizeQ > 0) {
            quotient[0] = 1;
        }
        break;
    case CMP_GREATER:
        n = msb(b, sizeB) + 1;
        m = msb(a, sizeA) + 1 - n;
        if (sizeQ == 0 && quotient != NULL) {
            sizeQ = n;
        }
        if (n + m <= BLOCK_SIZE) {
            if (quotient != NULL && sizeQ > 0) {
                quotient[0] = a[0] / b[0];
            }
            a[0] %= b[0];
        }
        else {
            t_size mswA = msw(a, sizeA);
            t_size sizeD = mswA + 1;
            t_bint* divider = new t_bint[sizeD];
            setNull(divider,sizeD);
            mov(divider,b,msw(b,sizeB) + 1);

            shl(divider,m,sizeD);

            unsigned char tmp_cmp, tmp;

            t_size i = m;
            while (true) {
                tmp_cmp = cmp(a,divider,sizeA,sizeD);
                tmp = (bool)(tmp_cmp & (CMP_EQUAL | CMP_GREATER));
                if (tmp) {
                    sub(a,divider,sizeA,sizeD);
                }
                if (quotient != NULL && sizeQ > 0) {
                    shl(quotient,1,sizeQ);
                    quotient[0] |= tmp;
                }

                // TODO: maybe modify the WHILE condition
                // or make it FOR?
                i--;
                if (i == -1) {
                    assert(cmp(divider,b,sizeD,sizeB) == CMP_EQUAL);
                    break;
                }
                assert(i >= 0);

                shr(divider,1,sizeD);
            }
            while (cmp(a,divider,sizeA,
                       sizeD) & (CMP_GREATER | CMP_EQUAL)) {
                sub(a,divider,sizeA,sizeD);
                if (quotient != NULL && sizeQ > 0) {
                    inc(quotient,sizeQ);
                }
            }
            delete[] divider;
        }
        break;
    default:
        // Something's gone bad
        assert(false);
        break;
    }
}

void div(t_bint* a, t_bint* b, t_size sizeA, t_size sizeB) throw (DBZException) {
    if (!sizeB || sizeB > sizeA) {
        sizeB = sizeA;
    }
    t_size sizeQ = sizeA;
    t_bint* quotient = new t_bint[sizeQ];
    mod(a,b,sizeA,sizeB,quotient,sizeQ);
    setNull(a,sizeA);
    mov(a,quotient,sizeQ);
    delete[] quotient;
}
