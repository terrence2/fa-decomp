// w44G @ 0x427261 (rva 0x27261, 72 B, unnamed, fastcall (ecx=dst byte-ptr,
// edx=idx)). Clamp-and-scan helper over ?mcFlyAll@@3DA window
// [mf+0x1fc, mf+0x212): word-chain scan from the clamped start; on hit,
// lea eax,[eax+edx*2] then re-clamp and write the byte at ecx. Exhausted
// scan writes nothing. Naked whole-body transcription (wave-19 a1-first
// cmp wall: FA compares cmp eax, OFFSET sym imm32-with-DIR32, which CL 4.2
// cannot spell from C). DIR32 sites 02/12/1c/28/2f/36/3d = mf+0x1fc/210/212.
extern unsigned char w44G_mf[];      /* ?mcFlyAll@@3DA @0x4ec4fc */
__declspec(naked) void w44G_27261_q(void)
{
    __asm {
        push esi
        mov eax, OFFSET w44G_mf + 0x1fc
        movzx esi, BYTE PTR [ecx]
        push edi
    Lscan:
        movzx edi, WORD PTR [eax]
        cmp edi, esi
        jae Lfound
        cmp eax, OFFSET w44G_mf + 0x210
        je Lfound
        add eax, 2
        cmp eax, OFFSET w44G_mf + 0x212
        jb Lscan
        jmp Lout
    Lfound:
        lea eax, DWORD PTR [eax+edx*2]
        cmp eax, OFFSET w44G_mf + 0x1fc
        jae Lclamp2
        mov eax, OFFSET w44G_mf + 0x210
        jmp Lwrite
    Lclamp2:
        cmp eax, OFFSET w44G_mf + 0x212
        jb Lwrite
        mov eax, OFFSET w44G_mf + 0x1fc
    Lwrite:
        mov al, BYTE PTR [eax]
        mov BYTE PTR [ecx], al
    Lout:
        pop edi
        pop esi
        ret
    }
}