// _nh_malloc @ rva 0xd92b0 (74 B) — CRT nlmalloc's core. FA loophead:
// [size>0xffffffe0 -> pv=0 b8 form]; pv==0 exit re-zero avoided by jumping
// straight to the exit when nhFlag==0 (74 0f). EXACT as plain C (wave-23
// probe): two tells — (1) the else-branch `pv = 0` (not a fallthrough
// omit) forces CL's mov eax,0 b8 imm32 loophead re-init, matching FA's
// 33 c0-vs-b8 choice; (2) `return pv` (not `return 0`) at the nhFlag check
// makes CL's je skip the re-zero, matching FA's 74 0f.
// Maps: _heapAllocX=__heap_alloc, _callnewhX=__callnewh.
extern void *heapAllocX(unsigned long);
extern unsigned long callnewhX(unsigned long);

void *__cdecl nh_malloc_q(unsigned long size, unsigned long nhFlag)
{
    void *pv;
    if (size > 0xffffffe0)
        return 0;
    if (size == 0)
        size = 1;
    for (;;)
    {
        pv = 0;
        if (size <= 0xffffffe0)
            pv = heapAllocX(size);
        else
            pv = 0;
        if (pv != 0)
            return pv;
        if (nhFlag == 0)
            return pv;
        if (callnewhX(size) == 0)
            return 0;
    }
}