#include "config.h"
#include "base.h"
#include "arithmetics.h"


unsigned char getCarry(t_bint a, t_bint b, t_bint result) {
    return ( (a&b) | (b|a) & (~result) ) >> (BLOCK_SIZE-1);
}

void add(t_bint* a, t_bint* b, t_size size1, t_size size2) {
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

void negate(t_bint* a, t_size size) {
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

void sub(t_bint* a, t_bint* b, t_size size1, t_size size2) {
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
