// w44G @ 0x45dc60 (rva 0x5dc60, 96 B, unnamed, fastcall (cx=ushort wing
// id)). Walks _wingIds entries (stride 10 words) while !_objPtrs[edx]&1,
// result = wingIds[10*id + hitCount] (word at ecx*2 offset). edx = counter,
// edi = id. 7-B zero-disp sib lea eax,[edi*4] + sib-soup walker = naked
// whole-body transcription. DIR32 sites 0d/25/31/50.
extern unsigned char w44G_ws[];      /* _wingSizes @0x5421b0 */
extern unsigned char w44G_wi[];      /* _wingIds @0x5421d0 */
extern unsigned char w44G_op[];      /* _objPtrs @0x54ad98 */
__declspec(naked) void w44G_5dc60_q(void)
{
    __asm {
        push ebx
        xor edx, edx
        push esi
        push edi
        movsx edi, cx
        push ebp
        xor ecx, ecx
        mov cl, BYTE PTR w44G_ws[edi]
        dec ecx
        test ecx, ecx
        jle Lend
        lea eax, DWORD PTR [edi*4]
        mov ebx, 1
        lea esi, DWORD PTR w44G_wi[eax+eax*4]
    Lloop:
        xor eax, eax
        mov ax, WORD PTR [esi]
        mov ebp, DWORD PTR w44G_op[eax*4]
        test DWORD PTR [ebp+1], ebx
        jnz Lend
        add esi, 2
        inc edx
        cmp edx, ecx
       jl Lloop
    Lend:
        lea eax, DWORD PTR [edi+edi*4]
        pop ebp
        pop edi
        pop esi
        lea ecx, DWORD PTR [edx+eax*2]
        pop ebx
        mov ax, WORD PTR w44G_wi[ecx*2]
        ret
        _emit 0x8d
        _emit 0x64
        _emit 0x24
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