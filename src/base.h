#include <string>
#include "assert.h"
// TODO: provide this enum
enum CmpResult { EQUAL, GREATER, LOWER };

const unsigned char CMP_EQUAL = 4;
const unsigned char CMP_GREATER = 1;
const unsigned char CMP_LOWER = 2;

const unsigned char LOG_INFO = 1;
const unsigned char LOG_WARNING = 1;
const unsigned char LOG_ERROR = 1;

#define LOG_LEVEL 0
void LOG(string message, unsigned char ll=LOG_INFO);
void displayBI(t_bint* a, t_size size=BLOCKS_NUMBER);
void scanBI(t_bint* a, const char* aStr, t_size sizeA=BLOCKS_NUMBER);
unsigned char cmp(t_bint* a, t_bint b, t_size size=BLOCKS_NUMBER);
unsigned char cmp(t_bint* a, t_bint* b,
                  t_size size1 = BLOCKS_NUMBER, t_size size2 = 0);
void mov(t_bint* a, t_bint* b, t_size size=BLOCKS_NUMBER);
t_size msw(t_bint* a, t_size size=BLOCKS_NUMBER);
t_size msb(t_bint* a, t_size size=BLOCKS_NUMBER);
bool isNull(t_bint* a, t_size size=BLOCKS_NUMBER);
void setNull(t_bint* a, t_size size=BLOCKS_NUMBER);
