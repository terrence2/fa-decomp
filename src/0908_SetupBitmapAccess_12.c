/* _SetupBitmapAccess@12 @ rva 0xa3cc0 (dec 670912), size 0x30 — EXACT,
 * pure C, no patches.
 *
 * fitobj: python3 tools/fitobj.py build/survey/probes/w24a_SetupBitmapAccess_v1.obj 670912 \
 *   --map '_brsColorProcess_x=_brsColorProcess' \
 *   --map '_averageTest_x=?averageTest@@3_JA' \
 *   build/survey/probes/w24a_SetupBitmapAccess_v1_fit.obj
 * (3 relocs DIR32: _brsColorProcess identity, ?averageTest@@3_JA with
 * +0x18/+0x1c built into the code displs. Stub-decomposition chunk. tail =
 * census-proven 17B filler incl. 8d ac 24 00 00 00 00.)
 */
extern unsigned char brsColorProcess_x[];
extern unsigned __int64 averageTest_x;
void __stdcall SetupBitmapAccess(short a, short b, short c)
{
    *(short *)(brsColorProcess_x) = a;
    *(short *)((char *)&averageTest_x + 0x1c) = b;
    *(short *)((char *)&averageTest_x + 0x18) = c;
}
