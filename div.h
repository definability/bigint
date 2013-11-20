void fDiv(t_bint* a, t_bint* b, t_bint* remainder=NULL,
          t_size size=BLOCKS_NUMBER, t_size sizeR=0);
void fDiv(t_bint* a, t_bint b, t_bint* remainder=NULL,
          t_size size=BLOCKS_NUMBER, t_size sizeR=0);
void divSS(t_bint* a, t_bint *b, t_bint* remainder=NULL,
           t_size sizeA=BLOCKS_NUMBER, t_bint sizeB=0, t_size sizeR=0);
void mod(t_bint* a, t_bint* b, t_size sizeA=BLOCKS_NUMBER, t_size sizeB=0,
         t_bint* quotient=NULL, t_size sizeQ=0);
void div(t_bint* a, t_bint* b, t_size sizeA=BLOCKS_NUMBER, t_size sizeB=0);
