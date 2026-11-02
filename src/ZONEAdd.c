/* ZONEAdd @ rva 0x217c0 (dec 137152), size 0x40 — EXACT, pure C, no patches.
 *
 * C recipe: 46-byte byte-array struct assignment inlined by CL 4.2 to
 * mov ecx,0xb / rep movsd / movsw; the count update is (*(short*)g)++
 * (66 ff 05 inc word). Globals spelled as cobraData_x (extern unsigned
 * char[]) mapped to FA's ?cobraData@@3UGlobalData@@A.
 *
 * fitobj: python3 tools/fitobj.py build/survey/probes/w24a_ZONEAdd_v1.obj 137152 \
 *   --map '_cobraData_x=?cobraData@@3UGlobalData@@A' \
 *   build/survey/probes/w24a_ZONEAdd_v1_fit.obj
 * (1 reloc DIR32 -> ?cobraData; tail census-proven.)
 */
typedef struct { char b[46]; } ZREC;
extern unsigned char cobraData_x[];
void __stdcall ZONEAdd(void *src)
{
    if (*(short *)(cobraData_x + 0xc1c0) < 6) {
        *(ZREC *)((char *)cobraData_x + 0xc1c8 + 46 * *(short *)(cobraData_x + 0xc1c0))
            = *(ZREC *)src;
        (*(short *)(cobraData_x + 0xc1c0))++;
    }
}
