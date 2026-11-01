// @MMPushAllocId@4 @ rva 0x35ca0 (32 B) — fastcall(id): dl=old mmAllocId
// (8a 15), eax=mm_unused_list+4 bump counter (a1), inc (40), mmAllocId=cl
// (88 0d), store counter (a3), an inline nop (90, reproduced from plain C
// — CL schedules it w14a_mmpush1), then the new-counter-indexed byte
// store at mmAllocId+3+eax (88 90, addend 3 baked in the C expression).
extern unsigned char mmAllocIdQ;   // ?mmAllocId@@3EA
extern long mmUnusedNextQ;         // ?mm_unused_list@@3PAUT_HANDLE@@A+0x4
extern char mmaSlots[];            // ?mmAllocId@@3EA (bare anchor; +3 in C)

void __fastcall MMPushAllocId(unsigned long id)
{
    unsigned char old;
    long n;

    old = mmAllocIdQ;
    n = mmUnusedNextQ;
    mmAllocIdQ = (unsigned char)id;
    n = n + 1;
    mmUnusedNextQ = n;
    mmaSlots[n + 3] = old;
}