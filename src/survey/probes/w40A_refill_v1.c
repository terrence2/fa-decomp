/* w40A_refill_v1 — unnamed 0x8b3c0 (64 B): stream refill loop */
#pragma pack(1)
typedef struct { char pad[0x12]; void* st; } SA;
#pragma pack()
typedef struct { int n; int lim; } SB;
extern void sub8b340(SA* a);

void sub8b3c0(SA* a, int amount)
{
    SB* b;
    b = (SB*)a->st;
    if (amount <= 0)
        return;
    while (b->lim < amount) {
        amount -= b->lim;
        sub8b340(a);
    }
    b->n += amount;
    b->lim -= amount;
}