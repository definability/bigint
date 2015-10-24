BigInt
======

My biginteger realization with Boost library tests. Just a lab for my university
- [x] Boolean arithmetic
- [x] Basic arithmetic
- [x] Class with overloaded operators
- [x] Modular arithmetic
- [x] Boost Test Library
- [x] GCD (Euclid + Binary)
- [x] LCM
- [x] Interface (read/write)

How to make
-----------
```bash
make all
```
command compiles it depending on your system architecture (64-bit or 32-bit). Executable is bigint

How to run
----------
Only testing at the moment

How to test
-----------
To see available tests type
```bash
make available_tests
```
To test one of them just type
```bash
make test_testname
```
To see only errors (or nothing if there are no errors) type
```bash
make test_testname_errors
```

###Time tests
```bash
make test_time
./tests/bin/time 1 1000
```
Usage of ```time```:
- If you execute ```time``` without parameters, you can see available test numbers
- First argument is the test number 
- Second argument is the number of BigIntegers to generate and operate
- Third argument is timeout in seconds (positive integer). Default is 10

###Memory leaks testing
Use valgrind. For example:
```bash
valgrind --track-origins=yes --tool=memcheck --leak-check=full ./tests/bin/time 5 1 2>err.log
```
Flag ```-g``` in ```g++``` allows you to see the line of code in which the memory leak could be fixed.
