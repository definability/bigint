#pragma once

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include "config.h"
#include "base.h"
#include "boolean.h"
#include "arithmetics.h"
#include "mul.h"
#include "div.h"
#include "modular.h"
#include "bigint.h"

using namespace std;

namespace random32 {
int Mersenne_32(int x, int i) {
    return 1812433253 * (x ^ (x >> 30)) + i;
}

int x = time(NULL);
int i = 0;

int rand32() {
    x = Mersenne_32(x,i);
    i++;
    return x;
}
}

namespace bigint {
void generateBI(t_bint* a, t_size sizeA = BLOCKS_NUMBER) {
    t_size i;
    t_size size = sizeA * BLOCK_SIZE / (8 * sizeof(int));
    int* tmp = (int*)a;
    for (i = 0; i < size; i++) {
        *tmp = random32::rand32();
        tmp++;
    }
}

class BigInt {
private:
    t_bint* value;     //[BLOCKS_NUMBER];

    void copy(const BigInt& source) {
        for (t_size i = 0; i < BLOCKS_NUMBER; i++) {
            this->value[i] = source[i];
        }
    }

    void copy(t_bint source) {
        for (t_size i = 1; i < BLOCKS_NUMBER; i++) {
            this->value[i] = 0;
        }
        this->value[0] = source;
    }

    /*
       void copy(t_sbint source) {
        if (source>0) {
            this->copy((t_bint)source);
        }
        else if (source==0) {
            this->setNull();
        }
        else {
            for (t_size i=1; i<BLOCKS_NUMBER; i++)
                this->value[i] = BLOCK_MAX_VALUE;
            this->value[0] = (t_bint)source-1;
        }
       }
     */

    void copy(t_bint* source, t_size size = BLOCKS_NUMBER) {
        this->setNull();
        for (t_size i = 0; i < size; i++) {
            this->value[i] = source[i];
        }
    }

    void setNull() {
        for (t_size i = 0; i < BLOCKS_NUMBER; i++) {
            this->value[i] = 0;
        }
    }
public:
    BigInt() {
        this->value = new t_bint[BLOCKS_NUMBER];
        this->setNull();
    }

    BigInt(const BigInt& source) {
        this->value = new t_bint[BLOCKS_NUMBER];
        this->copy(source);
    }

    BigInt(t_bint source) {
        this->value = new t_bint[BLOCKS_NUMBER];
        this->copy(source);
    }

    BigInt(int source) {
        this->value = new t_bint[BLOCKS_NUMBER];
        this->copy((t_bint)source);
    }

    BigInt(t_bint* source, t_size size = BLOCKS_NUMBER) {
        this->copy(source,size);
    }

    ~BigInt() {
        delete[] this->value;
    }

    BigInt& generate() {
        generateBI(this->value, BLOCKS_NUMBER);
        return *this;
    }

    t_size MSW() {
        return msw(this->value, BLOCKS_NUMBER);
    }

    t_size MSB() {
        return msb(this->value, BLOCKS_NUMBER);
    }

    BigInt& powMod(BigInt& p, BigInt& n) {
        pow_mod(this->value, p.value, n.value);
        return *this;
    }

    static BigInt MAX_VALUE() {
        BigInt result;
        result--;
        return result;
    }

    const t_bint operator[] (t_size i) const {
        return this->value[i];
    }

    /*
       BigInt& operator=(t_bint source) {
        this->copy(source);
       }
     */

    BigInt& operator=(const BigInt& source) {
        this->copy(source);
        return *this;
    }

    /*
       BigInt& operator=(t_sbint source) {
        this->copy(source);
       }
     */

    BigInt operator~() const {
        BigInt result(*this);
        for (int i = 0; i < BLOCKS_NUMBER; i++) {
            result.value[i] = ~(this->value[i]);
        }
        return result;
    }

    BigInt& operator>>=(const t_size shift) {
        shr(this->value,shift);
        return *this;
    }

    BigInt operator>>(const t_size shift) const {
        BigInt result(*this);
        result >>= shift;
        return result;
    }

    BigInt& operator<<=(const t_size shift) {
        shl(this->value,shift,BLOCKS_NUMBER);
        return *this;
    }

    BigInt operator<<(const t_size shift) const {
        BigInt result(*this);
        result <<= shift;
        return result;
    }

    BigInt& operator|=(const BigInt& operand) {
        for (t_size i = 0; i < BLOCKS_NUMBER; i++) {
            this->value[i] |= operand[i];
        }
        return *this;
    }

    BigInt operator|(const BigInt& operand) const {
        BigInt result(*this);
        result |= operand;
        return result;
    }

    BigInt& operator&=(const BigInt& operand) {
        for (t_size i = 0; i < BLOCKS_NUMBER; i++) {
            this->value[i] &= operand[i];
        }
        return *this;
    }

    BigInt operator&(const BigInt& operand) const {
        BigInt result(*this);
        result &= operand;
        return result;
    }

    BigInt& operator^=(const BigInt& operand) {
        for (t_size i = 0; i < BLOCKS_NUMBER; i++) {
            this->value[i] ^= operand[i];
        }
        return *this;
    }

    BigInt operator^(const BigInt& operand) const {
        BigInt result(*this);
        result ^= operand;
        return result;
    }

    BigInt& operator+=(const BigInt& source) {
        unsigned char carry = 0;         //, tmp_carry=0;
        t_bint tmp_value;
        for (t_size i = 0; i < BLOCKS_NUMBER; i++) {
            tmp_value = this->value[i];
            this->value[i] += source[i] + carry;
            carry =
                ( (tmp_value &
                   source[i]) |
                  ((source[i] |
                    tmp_value) &
                   (~this->value[i])) ) >> (BLOCK_SIZE - 1);
        }
        return *this;
    }

    BigInt operator+(const BigInt& operand) const {
        BigInt result(*this);
        result += operand;
        return result;
    }

    BigInt& operator++() {
        inc(this->value, BLOCKS_NUMBER);
        return *this;
    }

    BigInt operator++(int) {
        BigInt result(*this);
        inc(this->value, BLOCKS_NUMBER);
        return result;
    }

    BigInt& operator-=(BigInt source) {
        (*this) += ~source;
        (*this) += BigInt(1);
        return *this;
    }

    BigInt operator-(const BigInt& operand) const {
        BigInt result(*this);
        result -= operand;
        return result;
    }

    BigInt& operator--() {
        dec(this->value, BLOCKS_NUMBER);
        return *this;
    }

    BigInt operator--(int) {
        BigInt result(*this);
        dec(this->value, BLOCKS_NUMBER);
        return result;
    }

    BigInt& operator*=(const BigInt& source) {
        mul(this->value,source.value,BLOCKS_NUMBER);
        return *this;
    }

    BigInt operator*(const BigInt& source) const {
        BigInt result(*this);
        result *= source;
        return result;
    }

    friend BigInt operator*(t_bint operand1, const BigInt& operand2) {
        return operand2 * operand1;
    }

    BigInt& operator/=(const BigInt& source) {
        div(this->value,source.value);
        return *this;
    }

    BigInt operator/(const BigInt& source) const {
        BigInt result(*this);
        result /= source;
        return result;
    }

    friend BigInt operator/(t_bint operand1, const BigInt& operand2) {
        return BigInt(operand1) / operand2;
    }

    BigInt& operator%=(const BigInt& source) {
        mod(this->value, source.value);
        return *this;
    }

    BigInt operator%(const BigInt& source) const {
        BigInt result(*this);
        result %= source;
        return result;
    }

    friend BigInt operator%(t_bint operand1, const BigInt& operand2) {
        return BigInt(operand1) % operand2;
    }

    bool operator>=(const BigInt& source) const {
        return cmp(this->value,
                   source.value) & (CMP_GREATER | CMP_EQUAL);
    }

    bool operator==(const BigInt& source) const {
        return cmp(this->value, source.value) & CMP_EQUAL;
    }

    bool operator!=(const BigInt& source) const {
        return !(*this == source);
    }

    bool operator<=(const BigInt& source) const {
        return cmp(this->value, source.value) & (CMP_LOWER | CMP_EQUAL);
    }

    bool operator>(const BigInt& source) const {
        return cmp(this->value, source.value) & CMP_GREATER;
    }

    bool operator<(const BigInt& source) const {
        return cmp(this->value, source.value) & CMP_LOWER;
    }

    bool operator>=(const t_bint source) const {
        return cmp(this->value, source) & (CMP_GREATER | CMP_EQUAL);
    }

    bool operator==(const t_bint source) const {
        return cmp(this->value, source) & CMP_EQUAL;
    }

    bool operator<=(const t_bint source) const {
        return cmp(this->value, source) & (CMP_LOWER | CMP_EQUAL);
    }

    bool operator>(const t_bint source) const {
        return cmp(this->value, source) & CMP_GREATER;
    }

    bool operator<(const t_bint source) const {
        return cmp(this->value, source) & CMP_LOWER;
    }

    bool operator!=(const t_bint source) const {
        return !(*this == source);
    }

    explicit operator int() {
        return (int)this->value[0];
    }

    friend ostream& operator<<(ostream& os, const BigInt& bi) {
        t_size i = BLOCKS_NUMBER;
        while (i-- > 1 && bi[i] == 0) {}
        os << "0x";
        os << hex;
        if (i == 0) {
            os << (unsigned long long)bi[0];
            return os;
        }
        os << (unsigned long long)bi[i];
        while (i-- > 0) {
            os << setfill('0') <<
            setw(BLOCK_SIZE /
                 4) << (unsigned long long)bi[i];
        }
        return os;
    }

    friend istream& operator>>(istream& is, const BigInt& bi) {
        return is;
    }
};

BigInt gcdEuc(const BigInt& u, const BigInt& v) {
    if (u == 0) {
        return v;
    }
    else {
        return gcdEuc(v, u % v);
    }
}

BigInt gcdBin(const BigInt& u, const BigInt& v) {
    // simple cases (termination)
    if (u == v) {
        return u;
    }
    else if (u == 0) {
        return v;
    }
    else if (v == 0) {
        return u;
    }
    else if (~u & 1) { // u is even
        if (v & 1) { // v is odd
            return gcdBin(u >> 1, v);
        }
        else { // both u and v are even
            return gcdBin(u >> 1, v >> 1) << 1;
        }
    }
    else if (~v & 1) { // u is odd, v is even
        return gcdBin(u, v >> 1);
    }
    else if (u > v) { // reduce larger argument
        return gcdBin((u - v) >> 1, v);
    }
    else {
        return gcdBin((v - u) >> 1, u);
    }
}

BigInt lcm(const BigInt& u, const BigInt& v) {
    BigInt gcd = gcdBin(u,v);
    BigInt newU = u / gcd;
    BigInt newV = v / gcd;
    return newU * newV;
}
}