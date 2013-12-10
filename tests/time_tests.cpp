#include "time_tests.h"

BigInt* generate(int n) {
    BigInt* bigInts = new BigInt[n];
    for (t_size i = 0; i < n; i++) {
        bigInts[i].generate();
    }
    return bigInts;
}
int gen(int n) {
    BigInt* bigInts = generate(n);
    delete[] bigInts;
    return 0;
}
int add(int n) {
    BigInt* bigInts;
    bigInts = generate(n + 1);
    for (t_size i = 0; i < n; i++) {
        bigInts[i] += bigInts[i + 1];
    }
    delete[] bigInts;
    return 0;
}
int sub(int n) {
    BigInt* bigInts = generate(n + 1);
    for (t_size i = 0; i < n; i++) {
        bigInts[i] -= bigInts[i + 1];
    }
    delete[] bigInts;
    return 0;
}
int mul(int n) {
    BigInt* bigInts = generate(n + 1);
    for (t_size i = 0; i < n; i++) {
        bigInts[i] *= bigInts[i + 1];
    }
    delete[] bigInts;
    return 0;
}
int div(int n) {
    BigInt* bigInts = generate(n + 1);
    for (t_size i = 0; i < n; i++) {
        bigInts[i] /= bigInts[i + 1][0];
    }
    delete[] bigInts;
    return 0;
}
