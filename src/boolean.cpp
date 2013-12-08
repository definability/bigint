#include "config.h"
#include "base.h"
#include "boolean.h"

void swl(t_bint *a, t_size shift, t_size size) {
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

void swr(t_bint *a, t_size shift, t_size size) {
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

void shl(t_bint* a, t_size shift, t_size size) {
    if (shift==0) {
    }
    else if (shift>=size*BLOCK_SIZE) {

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
        for (i=size-1; i>=blockShift; i--) {
            a[i]=a[i-blockShift];
        }
        for (i=0; i<blockShift; i++) {
            a[i]=0;
        }
    }
    else {
        shl(a,shift-shift%BLOCK_SIZE,size);
        shl(a,shift%BLOCK_SIZE,size);
    }
}

void shr(t_bint* a, t_size shift, t_size size) {

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
        for (t_size i=size-blockShift; i<size; i++) {
            a[i]=0;
        }
    }
    else {
        shr(a,shift%BLOCK_SIZE);
        shr(a,shift-shift%BLOCK_SIZE);
    }

    return;
}
