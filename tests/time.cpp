#include <cstdlib>
#include <string>
#include "../src/bigint.cpp"
#include "time.h"
#include "time_tests.cpp"

using namespace std;
using namespace bigint;

typedef int (*tt1f)(int); // Time test (tt) functions (f) with 1 argument

string tests[] =
{ "Generation of random numbers", "Addition", "Subtraction", "Multiplication",
  "Division", "Power" };
tt1f funcs[] = { gen, add, sub, mul, div, pow };
const t_size TESTS_NUMBER = 6;

int main(int argc, char* argv[]) {
    t_size n;
    t_size test_number;

    if (argc < 2) {
        cerr << "Must be at least 1 argument" << endl;
        printHelp();
        return 1;
    }
    else if (argc == 2) {
        test_number = getArgv(argv[1]);
        if (test_number < 1 || test_number > TESTS_NUMBER) {
            cerr << "There are only " << TESTS_NUMBER << " tests" << endl;
            printHelp();
            return 1;
        }
        n = 100;
    }
    else if (argc == 3) {
        test_number = getArgv(argv[1]);
        if (test_number < 1 || test_number > TESTS_NUMBER) {
            cerr << "There are only " << TESTS_NUMBER << " tests" << endl;
            printHelp();
            return 1;
        }
        n = getArgv(argv[2]);
        if (n < 0) {
            cerr << "Invalid number " << argv[2] << endl;
            return 1;
        }
    }
    else {
        cerr << "Fatal error" << endl;
        return 1;
    }
    test_number--;
    cout << tests[test_number] << " time test started..." << endl;
    int result = funcs[test_number](n);
    cout << tests[test_number] << " time test completed ";
    if (result == 0) {
        cout << "successfully!" << endl;
    }
    else {
        cout << "with error code " << result << endl;
    }
    return result;
}

void printHelp() {
    cout << "Available tests:" << endl;
    for (t_size i = 0; i < TESTS_NUMBER; i++ ) {
        cout << i + 1 << ") " << tests[i] << endl;
    }
}

t_size getArgv(char argv[]) {
    char* endptr;
    t_size n = strtol(argv, &endptr, 10);
    if (!argv || *endptr) {
        cerr << "Invalid number " << argv[1] << endl;
        return -1;
    }
    return n;
}