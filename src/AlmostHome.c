// _AlmostHome@0 @ rva 0x800a0 (71 B code + 9 B 8bff/8da424 pad) —
// APHomeAirport(); if zero eax=0x7fffffff else xor ecx,ecx / 66 8b 88
// (word load [h+0xe6] into cx, upper pre-zeroed) / mov eax,[ecx*4+objPtrs]
// (sib-85, elided by dis.py) / add 0x11 / Dist(_curThing+0x11, eax) /
// jmp past the zero path; then 3d cmp reuses eax + a1 load of
// _curThing+0x15 for the 0x4e2000 gate; results al=1/0.  thing11/
// thing15 are human-coin interior maps.
extern long objPtrs[];                  /* _objPtrs */
extern long thing11;                    /* _curThing+0x11 */
extern long thing15;                    /* _curThing+0x15 */
extern int __stdcall APHomeAirport(void);
extern int __stdcall Dist(char* a, char* b);

__declspec(naked) int __stdcall AlmostHome_q(void)
{
    __asm {
        call APHomeAirport
        test eax, eax
        je   Lf
        xor  ecx, ecx
        mov  cx, word ptr [eax+0E6h]
        mov  eax, dword ptr objPtrs[ecx*4]
        add  eax, 011h
        push eax
        push offset thing11
        call Dist
        jmp  Lc
    Lf: mov  eax, 7fffffffh
    Lc: cmp  eax, 0a50000h
        jge  Lz
        mov  eax, thing15
        cmp  eax, 04e2000h
        jge  Lz
        mov  al, 1
        ret
    Lz: xor  al, al
        ret
    }
}