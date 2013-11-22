BigInt
======

My biginteger realization with Boost library tests. Just a lab for my university
- [x] Boolean arithmetic
- [x] Basic arithmetic
- [x] Class with overloaded operators
- [ ] Modular arithmetic
- [ ] Boost Test Library

How to make
-----------
```bash
make all
```
command compiles it depending on your system architecture (64-bit or 32-bit). Executable is bigint
How to run
----------
It's better to pipe stderr somewhere
```bash
./bigint 2>/dev/null
```
Errors have XML format, so you can do
```bash
./bigint 2>err.xml
```

Now it could be tested with Python:
```bash
./bigint 2>/dev/null 1>bigint_test.py
python bigint_test.py
```
It will be fixed in a month
