#include <cstdlib>
#include <string>
#include <exception>
#include <stdexcept>
#include <boost/test/included/prg_exec_monitor.hpp>
#include <boost/test/execution_monitor.hpp>
#include <boost/bind.hpp>
#include <boost/progress.hpp>
#include "../src/bigint.cpp"
#include "time.h"
#include "time_tests.cpp"

using namespace std;
using namespace bigint;

string tests[] =
{ "Generation of random numbers", "Addition", "Subtraction", "Multiplication",
  "Division", "Power" };
const t_size TESTS_NUMBER = 6;

int cpp_main(int argc, char* argv[]) {
    t_size n;
    int timeout = 10;
    t_size test_number;

    if (argc < 3) {
        if (argc == 2 && strcmp(argv[1], "--help") == 0) {
            printHelp(argv[0]);
            return 0;
        }
        else {
            cerr << "Must be at least 2 arguments" << endl;
            cerr << "Use --help to see the usage" << endl;
            printHelp(argv[0]);
            return 1;
        }
    }
    else {
        test_number = getArgv(argv[1]);
        if (test_number < 1 || test_number > TESTS_NUMBER) {
            cerr << "There are only " << TESTS_NUMBER << " tests" << endl;
            printHelp();
            return 1;
        }
        n = getArgv(argv[2]);
        if (argc > 3) {
            timeout = getArgv(argv[3]);
        }
    }
    test_number--;
    cout << tests[test_number] << " time test started..." << endl;
    boost::execution_monitor monitor;
    monitor.p_timeout.set(timeout);
    int result = 0;
    result = monitor.execute(boost::bind(test_something,n,test_number));
    cout << tests[test_number] << " time test completed ";
    if (result == 0) {
        cout << "successfully!" << endl;
    }
    else {
        cout << "with error code " << result << endl;
    }
    return result;
}

void printHelp(const char programName[]) {
    cout << endl;
    cout << "USAGE: " << programName <<
    " TEST_NUMBER REPEAT_TIMES [TIMEOUT_SEC=10]" << endl;
    cout << endl;
    cout <<
    "  TEST_NUMBER  is a number of the test from the following list:" << endl;
    for (t_size i = 0; i < TESTS_NUMBER; i++ ) {
        cout << "    [" << i + 1 << "] " << tests[i] << endl;
    }
    cout << endl;
    cout << "  REPEAT_TIMES is a number of iterations of every test" << endl;
    cout << endl;
    cout <<
    "  TIMEOUT_SEC  is a time in seconds what you are ready to wait." << endl;
    cout << "               Standard value is 10" << endl;
    cout << endl;
    cout << "  EXAMPLES:" << endl;
    cout << "    " << programName << " 1 1000000" << endl;
    cout << "        will cause million times BigInt generation" << endl;
    cout << endl;
    cout << "    " << programName << " 6 10 100" << endl;
    cout <<
    "        will cause ten times BigInt power by modulus and will be" << endl;
    cout <<
    "        aborted if the timeout will reach the 100 seconds barier" << endl;
    cout << endl;
}

long getArgv(char argv[]) {
    char* endptr;
    long n = strtol(argv, &endptr, 10);
    if (!argv || *endptr) {
        throw std::runtime_error(string("Invalid number ") + string(argv));
    }
    return n;
}
