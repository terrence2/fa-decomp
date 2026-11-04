/* _StreamersUpdate@0 (rva 0x9e270, 128 B, __cdecl, 3-dword local):
 * per-plane streamer tick. While (short)_numPlanes > 0, walk the plane
 * table _planes (WORD ids, edi += 2 per iteration) with objPtrs[p] (SIB
 * eax*4+disp32 load into ebp) and, when the object's flag dword at
 * [obj+1] has bit 0 set (f6 c1 01 test cl,1), run the still-stub plane
 * getter $FA$_t_49e130(obj, 0|1, &localBuf) and pipe the filled buffer
 * through __fastcall @SampleUpdate@8 into the two stride-0x14 slots
 * (_planes+0x80 + 0x14*i and _numPlanes+0x8 + 0x14*i). The loop bottom
 * re-materializes (movsx) numPlanes every iteration - FA's scheduler
 * shape, kept verbatim by the transplant.
 */
extern short numPlanes;                          /* _numPlanes */
extern unsigned short planes[];                  /* _planes */
extern void *objPtrs[];                          /* _objPtrs */
extern void __fastcall SampleUpdate(void *out, long *buf);
extern void __fastcall FA_t_49e130(void *o, long which, long *buf);

void __cdecl w44e_StreamersUpdate(void)
{
    long buf[3];
    long n = numPlanes;
    int i;
    if (n > 0)
        for (i = 0; i < n; i++) {
            void *o = objPtrs[planes[i]];
            if (*(long *)((char *)o + 1) & 1) {
                FA_t_49e130(o, 0, buf);
                SampleUpdate((char *)planes + 0x80 + 0x14 * i, buf);
                FA_t_49e130(o, 1, buf);
                SampleUpdate((char *)&numPlanes + 8 + 0x14 * i, buf);
            }
        }
}