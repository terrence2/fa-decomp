// @MMPopAllocId@0 @ rva 0x35cc0 (32 B) — bump-pop of the mm unused-list
// counter: a1/dec/a3 on ?mm_unused_list+0x4, byte lookup at ?mmAllocId+0x4,
// a2 moffs store + ret-al. probe w12a_06 byte-exact.
extern long mmUnusedNextQ;
extern char mmaTable[];
extern unsigned char mmAllocIdQ;

unsigned char __fastcall MMPopAllocId_q(void)
{
    long id;
    unsigned char b;

    id = mmUnusedNextQ;
    id = id - 1;
    mmUnusedNextQ = id;
    b = *(unsigned char *)(mmaTable + id);
    mmAllocIdQ = b;
    return b;
}
