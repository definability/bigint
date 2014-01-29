#include "config.h"
#include "base.h"
#include "boolean.h"
#include "arithmetics.h"
#include "mul.h"

inline void mulWords(t_bint* a, t_bint b) {
    asm (
        "mul %3"
        : "=a" (a[0]), "=d" (a[1])
        : "a" (*a), "d" (b)
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
            t_size sizeW = mswA + mswB + 2;
            t_size sizeT = 4;
            t_size sizeTmp = 2;
            t_bint* t = new t_bint[sizeT];
            t_bint* tmp = new t_bint[sizeTmp];
            setNull(t,sizeT);
            setNull(tmp,sizeTmp);
            t_bint* w = new t_bint[sizeW];
            setNull(w,sizeW);
            for (s = 0; s < sizeW; s++) {
                for (i = s; i >= 0; i--) {
                    if (mswA > i && mswB > s - i) {
                        tmp[0] = a[i];
                        mulWords(tmp,b[s - i]);
                        add(t,tmp,sizeT,sizeTmp);
                        setNull(tmp,sizeTmp);
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
            delete[] tmp;
            delete[] t;
        }
    }
}

/**
 * Karatsuba's multiplication method (a=a*b).
 * That's why parameter `a' must have the resulting length.
 */
void mulK(t_bint* a, t_bint* b, t_size sizeA, t_size sizeB) {
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
            /*
               mov(a,mulWords(a[0],b[0]),2);
             */
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
            n = (mswA > mswB ? mswA : mswB);
            n = n / 2 + n % 2;
            t_size sizeR = 4 * n;
            t_size sizeX0 =
                n<mswA ? n : mswA,
                  sizeX1 = mswA>sizeX0 ? mswA - sizeX0 : 0,
                   sizeY0 =
                n<mswB ? n : mswB,
                  sizeY1 = mswB>sizeY0 ? mswB - sizeY0 : 0;
            t_bint** x = new t_bint *[2],
            ** y = new t_bint *[2],
            * tmp = new t_bint[sizeR],
            * result = new t_bint[sizeR];
            //n*=BLOCK_SIZE;
            // Initialize X0, X1
            x[0] = new t_bint[sizeX0];
            for (i = 0; i < sizeX0; i++) {
                x[0][i] = a[i];
            }
            if (sizeX1) {
                x[1] = new t_bint[sizeX1];
                for (i = 0; i < sizeX1; i++) {
                    x[1][i] = a[i + sizeX0];
                }
            }
            else {
                x[1] = new t_bint[sizeX1];
            }
            // Initialize Y0, Y1
            y[0] = new t_bint[sizeY0];
            for (i = 0; i < sizeY0; i++) {
                y[0][i] = b[i];
            }
            if (sizeY1) {
                y[1] = new t_bint[sizeY1];
                for (i = 0; i < sizeY1; i++) {
                    y[1][i] = b[i + sizeY0];
                }
            }
            else {
                y[1] = new t_bint[sizeY1];
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
            if (!isNull(x[0],sizeX0) && !isNull(y[0],sizeY0)) {
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
            if (!sizeX1) {
                cmpX0X1 = CMP_GREATER;
            }
            else {
                cmpX0X1 = cmp(x[0],x[1],sizeX0,sizeX1);
            }
            if (!sizeY1) {
                cmpY0Y1 = CMP_GREATER;
            }
            else {
                cmpY0Y1 = cmp(y[0],y[1],sizeY0,sizeY1);
            }
            if (cmpX0X1 != CMP_EQUAL && cmpY0Y1 != CMP_EQUAL) {
                if (cmpX0X1 == CMP_LOWER) {
                    sub(x[1],x[0],sizeX1, sizeX0);
                    mov(x[0],x[1],sizeX1);
                    sizeX0 = sizeX1;
                }
                else if (cmpX0X1 == CMP_GREATER && sizeX1 !=
                         0) {
                    sub(x[0],x[1],sizeX0, sizeX1);
                }
                if (cmpY0Y1 == CMP_GREATER && sizeY1 != 0) {
                    sub(y[0],y[1],sizeY0, sizeY1);
                }
                else if (cmpY0Y1 == CMP_LOWER) {
                    sub(y[1],y[0],sizeY1, sizeY0);
                    mov(y[0],y[1],sizeY1);
                    sizeY0 = sizeY1;
                }
                mov(tmp,x[0],sizeX0);
                mul(tmp,y[0],sizeR,sizeY0);
                swl(tmp,n,sizeR);
                if ((cmpX0X1 ==
                     CMP_GREATER) ^ (cmpY0Y1 == CMP_LOWER)) {
                    sub(result,tmp,sizeR,sizeR);
                }
                else {
                    add(result,tmp,sizeR,sizeR);
                }
            }
            setNull(a,sizeA);
            mov(a,result,sizeR < sizeA ? sizeR : sizeA);
            delete[] tmp;
            delete[] x[0];
            delete[] x[1];
            delete[] x;
            delete[] y[0];
            delete[] y[1];
            delete[] y;
            delete[] result;
        }
    }
}

void sqr(t_bint* a, t_size sizeA) {
    mul(a,a,sizeA,sizeA);
}