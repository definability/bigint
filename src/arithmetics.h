unsigned char getCarry(t_bint a, t_bint b, t_bint result);
void add(t_bint* a, t_bint* b, t_size size1, t_size size2 = 0);
void negate(t_bint* a, t_size size = BLOCKS_NUMBER);
void sub(t_bint* a, t_bint* b, t_size size1 = BLOCKS_NUMBER, t_size size2 = 0);