#include "time_tests.h"
#include <boost/progress.hpp>
#include <boost/thread.hpp>

typedef int (*ti1f)(BigInt*); // Test iteration (ti) functions (f) with 1 argument

struct TestableFunctionIteration {
    ti1f f;
    int bigintsNeeded;
    TestableFunctionIteration(ti1f f,
                              int bigintsNeeded) : f(f),
                                                   bigintsNeeded(bigintsNeeded)
    {
    }
};

TestableFunctionIteration fIters[] = {
    TestableFunctionIteration(genI, 1),
    TestableFunctionIteration(addI, 2),
    TestableFunctionIteration(subI, 2),
    TestableFunctionIteration(mulI, 2),
    TestableFunctionIteration(divI, 2),
    TestableFunctionIteration(powI, 3)
};

BigInt* generate(int n) {
    boost::progress_display show_progress(n);
    BigInt* bigInts = new BigInt[n];
    for (t_size i = 0; i < n; i++) {
        bigInts[i].generate();
        ++show_progress;
    }
    return bigInts;
}

int genI(BigInt* bigInts) {
    bigInts->generate();
    return 0;
}
int addI(BigInt* bigInts) {
    bigInts[0] += bigInts[1];
    return 0;
}
int subI(BigInt* bigInts) {
    bigInts[0] -= bigInts[1];
    return 0;
}
int mulI(BigInt* bigInts) {
    bigInts[0] *= bigInts[1];
    return 0;
}
int divI(BigInt* bigInts) {
    bigInts[0] /= bigInts[1][0];
    return 0;
}
int powI(BigInt* bigInts) {
    bigInts[0].powMod(bigInts[1],bigInts[2]);
    return 0;
}

int test_something(int n, int functionNumber) {
    TestableFunctionIteration iter = fIters[functionNumber];
    BigInt* bigInts;
    boost::timer t;
    if (functionNumber == 0) {
        bigInts = new BigInt[n];
    }
    else {
        cout << endl;
        cout << "Generating sequence of BigInts";
        t.restart();
        bigInts = generate(n + iter.bigintsNeeded - 1);
        cout << "Generated in " << t.elapsed() << " s" << endl;
    }

    cout << endl;
    cout << "Testing";
    boost::progress_display show_progress(n);
    t.restart();
    for (int i = 0; i < n; i++) {
        iter.f(&bigInts[i]);
        ++show_progress;
    }
    cout << "Completed in " << t.elapsed() << " s" << endl;
    delete[] bigInts;
    return 0;
}