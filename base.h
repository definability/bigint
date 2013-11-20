// TODO: provide this enum
enum CmpResult { EQUAL, GREATER, LOWER };

const unsigned char CMP_EQUAL = 0;
const unsigned char CMP_GREATER = 1;
const unsigned char CMP_LOWER = 2;

unsigned char cmp(t_bint* a, t_bint b, t_size size=BLOCKS_NUMBER);
unsigned char cmp(t_bint* a, t_bint* b,
                  t_size size1 = BLOCKS_NUMBER, t_size size2 = 0);
void mov(t_bint* a, t_bint* b, t_size size=BLOCKS_NUMBER);
t_size msw(t_bint* a, t_size size=BLOCKS_NUMBER);
t_size msb(t_bint* a, t_size size=BLOCKS_NUMBER);
bool isNull(t_bint* a, t_size size=BLOCKS_NUMBER);
void setNull(t_bint* a, t_size size=BLOCKS_NUMBER);
