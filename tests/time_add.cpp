#include <cstdlib>
#include "../src/bigint.cpp"

using namespace bigint;

int main(int argc, char* argv[]) {
    t_size n;
    if (argc == 1) {
        n = 100;
    }
    else if (argc > 1) {
        char* endptr;
        n = strtol(argv[1], &endptr, 10);
        if (!argv[1] || *endptr) {
            cerr << "Invalid number " << argv[1] << endl;
            return 1;
        }
    }
    else {
        cerr << "Fatal error" << endl;
        assert(false);
    }
    BigInt* bigInts = new BigInt[n];
    for (t_size i = 0; i < n; i++) {
        bigInts[i].generate();
    }
    for (t_size = 0; i < n; i++) {
        bigInts[i] += bigInts[i];
    }
    delete[] bigInts;
    return 0;
}