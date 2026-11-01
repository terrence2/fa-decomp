// @COLGetBox@8 @ rva 0x2dc30 (64 B) — fastcall (id in ecx unused, find in edx).
// COLGetInfo@4 is callee-cleans (ret 4): CL emits push ecx / mov esi,edx /
// call — the param spill goes AFTER the arg push (wave-7 post-push rule).
// The box walk needs tag-test-in-if + do-while INSIDE the if so the clear-tag
// exit is a shared fallthrough (je +0x14 over the loop), not an inline
// duplicate (probe w12a_15; w12a_03's flat form gave jne-inline + dup exit).
extern long __stdcall COLGetInfo(long id);
long __fastcall COLGetBox_q(long id, long find)
{
    long info;
    unsigned char tag;
    long w;

    info = COLGetInfo(id);
    if (info == 0)
        return 0;
    tag = *(unsigned char *)((char *)info + 0x10);
    info = (char *)info + 0x10;
    if (tag & 0x80)
    {
        do
        {
            w = *(unsigned char *)((char *)info + 1);
            if (w == find)
                return (long)info;
            tag = *(unsigned char *)((char *)info + 0xe);
            info = (char *)info + 0xe;
        } while (tag & 0x80);
    }
    return 0;
}
