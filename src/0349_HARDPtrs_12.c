// w44G @ 0x451d90 (rva 0x51d90, 128 B) _HARDPtrs@12: void _HARDPtrs(long n,
// HARDPOINT **out1, HARDPOINT_TYPE **out2) ebp-frame, 8-B locals, ret 0xc.
// Computes &curThing[n*17] and &curThingType[0xb6 + n*24] with the
// ebx-accumulator walk (n<<4; +n; 3n; +hb; +&_curThing) and two
// default-arg leas. nops at 09/5e = FA codegen residue carried in-body.
// Naked whole-body transcription. DIR32 sites 13/37/47/4f.
extern unsigned char w44G_ct[];      /* _curThing @0x508738 */
extern unsigned char w44G_ctt[];     /* _curThingType @0x508b20 */
__declspec(naked) void _HARDPtrs(long a, void *b, void *c)
{
    __asm {
        mov eax, DWORD PTR [esp+4]
        sub esp, 8
        test eax, eax
        nop
        push ebx
        push esi
        push ebp
        jl Lfail
        xor ecx, ecx
        mov cl, BYTE PTR w44G_ctt[0xb5]
        cmp ecx, eax
        jle Lfail
        mov esi, DWORD PTR [esp+0x1c]
        test esi, esi
        jne L1
        lea esi, DWORD PTR [esp+0x10]
    L1:
        mov edx, DWORD PTR [esp+0x20]
        test edx, edx
        jne L2
        lea edx, DWORD PTR [esp+0xc]
    L2:
        mov ecx, eax
        mov ebx, DWORD PTR w44G_ct[0x114]
        shl ecx, 4
        add ecx, eax
        lea eax, DWORD PTR [eax+eax*2]
        add ecx, ebx
        add ecx, OFFSET w44G_ct
        mov DWORD PTR [esi], ecx
        mov ebp, DWORD PTR w44G_ctt[0xb6]
        lea eax, DWORD PTR [ebp+eax*8]
        pop ebp
        mov DWORD PTR [edx], eax
        mov ecx, DWORD PTR [esi]
        pop esi
        pop ebx
        nop
        mov eax, DWORD PTR [ecx]
        add esp, 8
        ret 0xc
    Lfail:
        xor eax, eax
        pop ebp
        pop esi
        pop ebx
        add esp, 8
        ret 0xc
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
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