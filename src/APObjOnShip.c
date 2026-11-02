// @APObjOnShip@4 @ rva 0xbb1d0 (766416) — 47 B code + 90 pad. Pure CL C —
// EXACT fit, no patches (probes v2..v4).
//
// The FA shape (cursor in eax, entry ptr cached in ebx with a SECOND read
// of [s+2] on the found path, bound as a direct cmp eax,imm32, and the dead
// xor edx,edx at entry) falls out of a do-while with the obj field read
// TWICE through distinct typed expressions — the test reads *(void**)(s+2)
// and the return re-derives through *(unsigned long *)(s + 2), which also
// reuses the cursor register (eax) for the reload+mov ax,[+0xe6]. Probe v2
// (while loop + o local) staged the bound in a register and read the field
// once — wrong rotation and wrong reg home; v4 (r=0 accumulator) moved the
// return into esi and gained push/pop esi. v3's plain do-while + double
// read reproduced every byte including the dead xor.
//
// Maps: _apShipBaseQ=_airports+0x3020 (a1 imm at chunk off 2, HIGHLOW).
// _overflow_ptr is the identity FA anchor (cmp eax,imm32 at off 24).
extern char apShipBaseQ[];
extern char overflow_ptr;

unsigned short __fastcall APObjOnShip(unsigned short thing)
{
    char *s = apShipBaseQ;
    do {
        if (*(unsigned short *)s == thing)
            if (*(void **)(s + 2) != 0)
                return *(unsigned short *)(*(unsigned long *)(s + 2) + 0xe6);
        s += 0x18;
    } while ((char *)s < &overflow_ptr);
    return 0;
}