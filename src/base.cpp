#include "config.h"
#include "base.h"


void LOG(string message, unsigned char ll) {
    if (LOG_LEVEL&ll) cerr<<message<<endl;
}

unsigned char cmp(t_bint* a, t_bint b, t_size size) {
    if (a[0]>b) return CMP_GREATER;
    for (t_size i=1; i<size; i++) {
        if (a[i])
            return CMP_GREATER;
    }
    if (a[0]==b) return CMP_EQUAL;
    if (a[0]<b) return CMP_LOWER;
}

unsigned char cmp(t_bint* a, t_bint* b, t_size size1, t_size size2) {
    if (!size2) size2=size1;
    t_size i;
    if (size1>size2) {
        for (i=size1-1; i>=size2; i--) {
            if (a[i])
                return CMP_GREATER;
        }
    }
    else if (size2>size1) {
        for (i=size2-1; i>=size1; i--) {
            if (b[i])
                return CMP_LOWER;
        }
    }
    else
        i=size1-1;
    for (; i>=0; i--) {
        if (a[i]>b[i])
            return CMP_GREATER;
        else if (a[i]<b[i])
            return CMP_LOWER;
    }
    return CMP_EQUAL;
}

void mov(t_bint* a, t_bint* b, t_size size) {
    for (t_size i=0; i<size; i++)
        a[i]=b[i];
}

t_size msw(t_bint* a, t_size size) {
    while (--size>=0) {
        if (a[size]>0)
            return size;
    }

    return -1;
}

t_size msb(t_bint* a, t_size size) {
    t_size result = msw(a,size);
    t_size i;
    if (result==-1)
        return -1;
    t_bint tmp=a[result];
    result*=BLOCK_SIZE;
    for (i=0; i<BLOCK_SIZE; i++) {
        tmp>>=1;
        if (!tmp)
            return result+i;
    }
    return -2;
}

bool isNull(t_bint* a, t_size size) {
    if (!a || !size)
        return true;
    while (size-->0) {
        if (a[size])
            return false;
    }
    return true;
}

void setNull(t_bint* a, t_size size) {
    while (size-->0) {
        a[size]=0;
    }
}
