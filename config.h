#include <cstdlib>
#include <iostream>

typedef long t_size;

typedef unsigned long ULONG;
typedef unsigned long t_bint;
typedef signed long t_sbint;
typedef long double t_float;
/*
typedef unsigned char t_bint;
typedef signed char t_sbint;
*/

//TODO: bits->bytes sizes
const unsigned long BLOCK_SIZE = 8*sizeof(t_bint); //64;
const unsigned long NUMBER_CAPACITY = (long)1<<8;
const unsigned long BLOCKS_NUMBER = NUMBER_CAPACITY/BLOCK_SIZE;
const unsigned long ULONG_SIZE = sizeof(ULONG);

const t_bint BLOCK_MAX_VALUE = 0xFFFFFFFFFFFFFFFF;
const t_bint BLOCK_MAX_BIT = (long)1<<(BLOCK_SIZE-1);

const unsigned char CMP_EQUAL = 0;
const unsigned char CMP_GREATER = 1;
const unsigned char CMP_LOWER = 2;

using namespace std;
