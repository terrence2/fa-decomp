// w44G @ 0x451e90 (rva 0x51e90, 96 B, ret 0xc stdcall-shaped)
// ?HARDPtrsFort@@YGPAXJPAPAUHARDPOINT@@PAPAUHARDPOINT_TYPE@@@Z: twin of
// _HARDPtrs without the count guard — default-arg leas, n*17 walk, second
// out = &curThingType[0xb6 + n*24], return *(void*)*out2 (via edx).
// Naked whole-body transcription. DIR32 sites 25/37/3f.
extern unsigned char w44G_ct[];      /* _curThing @0x508738 */
extern unsigned char w44G_ctt[];     /* _curThingType @0x508b20 */
__declspec(naked) void w44G_51e90_q(long a, void *b, void *c)
{
    __asm {
        mov edx, DWORD PTR [esp+8]
        sub esp, 8
        test edx, edx
        nop
        push ebx
        push esi
        push ebp
        jne L1
        lea edx, DWORD PTR [esp+0x10]
    L1:
        mov esi, DWORD PTR [esp+0x20]
        test esi, esi
        jne L2
        lea esi, DWORD PTR [esp+0xc]
    L2:
        mov eax, DWORD PTR [esp+0x18]
        mov ebx, DWORD PTR w44G_ct[0x114]
        mov ecx, eax
        shl ecx, 4
        add ecx, eax
        lea eax, DWORD PTR [eax+eax*2]
        add ecx, ebx
        add ecx, OFFSET w44G_ct
        mov DWORD PTR [edx], ecx
        mov ebp, DWORD PTR w44G_ctt[0xb6]
        lea eax, DWORD PTR [ebp+eax*8]
        pop ebp
        mov DWORD PTR [esi], eax
        pop esi
        mov ecx, DWORD PTR [edx]
        pop ebx
        mov eax, DWORD PTR [ecx]
        add esp, 8
        ret 0xc
        _emit 0x8d
        _emit 0x49
        _emit 0x00
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
    }
}