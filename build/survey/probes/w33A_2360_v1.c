extern unsigned long timerTicks;

typedef struct W33T {
    unsigned char pad0[4];
    long f4;
    long f8;
    unsigned char pad17[0x0e];
    unsigned char f1a;
} W33T;

void w33A_2360_v1(W33T *t)
{
    unsigned char b;
    t->f8 = timerTicks;
    b = t->f1a;
    if (!b)
        t->f4 = 4;
}