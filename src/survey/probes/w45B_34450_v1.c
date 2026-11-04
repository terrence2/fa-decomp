/* ?UpdateLoopSounds@@YIXXZ @ rva 0x34450 (176 B, FPO/esp, census tail pad
 * 8d9b00000000+8da42400000000) -- w45B v1. Naked-asm transcription. Walks
 * loopSnd records (stride 0x26, 4 records; bound = &mm_page_size which sits
 * right after loopSnd). Per record: [esi+0x22] status word; 0 -> power down
 * (SoundOff when [esi+0x12]!=0xffff, then stage 0xffff/'di'/0x7fff); 1 ->
 * SoundOn with 15 pushed args built right-to-left from record words
 * ([esi+0x20..0x18] 32-bit pushes of word regs, cl=[esi+0x16] byte, 0x64,
 * [esi+0x24], [esi+0x10], 1, 0xff, [esi+0x12-ish] cx, esi), store result to
 * [esi+0x12], stage status=2. Naked asm: exact interleaved load/push order,
 * 16-bit chains, 68-form imm32 pushes (6a form would shift sizes). */
extern char loopSnd[];                       /* _loopSnd */
extern unsigned long mm_page_size;           /* _mm_page_size */
extern void __fastcall SoundOff(short x);    /* @SoundOff@4 */
extern void __stdcall SoundOn(long, long, long, long, long, long, long,
                              long, long, long, long, long, long, long,
                              long);         /* _SoundOn@60 */

void __declspec(naked) UpdateLoopSounds_45b(void)
{
    __asm {
        push ebx
        push esi
        push edi
        mov  esi, offset loopSnd
        xor  edi, edi
        mov  ebx, 0x7fff
w45buls_loop:
        mov  ax, word ptr [esi+0x22]
        test ax, ax
        jne  w45buls_on
        mov  cx, word ptr [esi+0x12]
        cmp  cx, -1
        je   w45buls_next
        call SoundOff
        mov  word ptr [esi+0x12], 0xffff
        mov  word ptr [esi+0x10], di
        mov  word ptr [esi+0x14], bx
        jmp  w45buls_next
w45buls_on:
        cmp  ax, 1
        jne  w45buls_next
        mov  cx, word ptr [esi+0x12]
        cmp  cx, -1
        je   w45buls_s2
        call SoundOff
w45buls_s2:
        mov  ax, word ptr [esi+0x20]
        push 0xffffffff
        mov  cx, word ptr [esi+0x1e]
        push edi
        mov  dx, word ptr [esi+0x1c]
        push edi
        push eax
        push ecx
        mov  ax, word ptr [esi+0x1a]
        push edx
        mov  dx, word ptr [esi+0x18]
        push eax
        mov  ax, word ptr [esi+0x10]
        mov  cl, byte ptr [esi+0x16]
        push ecx
        push 0x64
        mov  cx, word ptr [esi+0x24]
        push edx
        push eax
        push 1
        push 0xff
        push ecx
        push esi
        call SoundOn
        mov  word ptr [esi+0x12], ax
        mov  word ptr [esi+0x22], 2
w45buls_next:
        add  esi, 0x26
        cmp  esi, offset mm_page_size
        jb   w45buls_loop
        pop  edi
        pop  esi
        pop  ebx
        ret
    }
}