#define TRUE 1
#define FALSE 0
#define HW_REG(a) *((unsigned int*) a)
#define BARRIER() asm("" : : : "memory")
