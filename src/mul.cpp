#include "config.h"
#include "base.h"
#include "boolean.h"
#include "arithmetics.h"
#include "mul.h"

inline void mulWords(t_bint* a, t_bint b) {
    asm (
        "mul %[operand]"
        : "=a" (a[0]), "=d" (a[1])
        : "a" (*a), [operand] "d" (b)
        );
}

inline void mulIteration(t_bint* result, t_bint a, t_bint b) {
    asm (
            "mul %[mul_rh];"
            "add %[mul_rl], (%[result]);"

            "adc %[mul_rh], (%[result], %[index], 8);"

            "inc %[index];"
            "adc $0, (%[result], %[index], 8);"
            : 
            : [mul_rl] "a" (a)
            , [mul_rh] "d" (b)
            , [result] "b" (result)
            , [index] "c" ((t_bint)1)
            );
}

void mul(t_bint* a, t_bint* b, t_size sizeA, t_size sizeB) {
    if (!sizeB || sizeB > sizeA) {
        sizeB = sizeA;
    }
    if (isNull(a, sizeA) || isNull(b, sizeB)) {
        setNull(a, sizeA);
    }
    else if (sizeA == 1) {
        a[0] *= b[0];
    }
    else {
        t_size mswA = msw(a,sizeA), mswB = msw(b,sizeB);
        if ((mswA | mswB) == 0) {
            mulWords(a, *b);
        }
        else {
            mswA++;
            mswB++;
            t_size s, i;
            t_size sizeW = mswA + mswB;
            t_size sizeT = 3;
            t_bint* t = new t_bint[sizeT];
            setNull(t,sizeT);
            t_bint* w = new t_bint[sizeW];
            setNull(w,sizeW);
            for (s = 0; s < sizeW; s++) {
                for (i = s; i >= 0; i--) {
                    if (mswA > i && mswB > s - i) {
                        mulIteration(t, a[i], b[s-i]);
                        isNull(t,0); // FIXME: memory error without this
                    }
                }
                w[s] = t[0];
                swr(t,1,sizeT);
            }
            if (sizeA > sizeW) {
                mov(a,w,sizeW);
                setNull(&a[sizeW],sizeA - sizeW);
            }
            else {
                mov(a,w,sizeA);
            }
            delete[] w;
            delete[] t;
        }
    }
}

void sqr(t_bint* a, t_size sizeA) {
    mul(a,a,sizeA,sizeA);
}
