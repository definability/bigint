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
        cerr << "Must be at least 2 arguments: test_number repeat_times [timeout_sec]" << endl;
        printHelp();
        return 1;
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

void printHelp() {
    cout << "Available tests:" << endl;
    for (t_size i = 0; i < TESTS_NUMBER; i++ ) {
        cout << i + 1 << ") " << tests[i] << endl;
    }
}

long getArgv(char argv[]) {
    char* endptr;
    long n = strtol(argv, &endptr, 10);
    if (!argv || *endptr) {
        throw std::runtime_error(string("Invalid number ") + string(argv));
    }
    return n;
}
