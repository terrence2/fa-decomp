// unnamed chunk @ rva 0x4cd0, VA 0x404cd0 (80 B; code 71 B + tail
// 8b ff / 8d a4 24 00 00 00 00).  cdecl, no args read.  Wall: f3 a6 repz
// cmpsb string compare of ?seqLine@@3PADA vs the .rdata literal at
// VA 0x4f0e20 (=?valkyriesScore@@3DA+0x720) — no C form (wave-16 rule).
// Whole-body naked-asm transcription (w41F CopyDB15 recipe; repz pair
// spelled _emit to dodge /O2 asm rewriting).  Semantics: if
// strncmp(seqLine, LIT, 7) == 0, find the two quote pairs in seqLine,
// return pointer past the opening quote of the 2nd pair and NUL the
// closing quote; else return 0.
extern char w43H_seqLine[];  /* =?seqLine@@3PADA */
extern char w43H_lit[];      /* =?valkyriesScore@@3DA+0x720 */

__declspec(naked) long __cdecl w43H_44cd0_scmp(void)
{
    __asm {
        push esi
        mov edx, OFFSET w43H_seqLine
        push edi
        mov esi, edx
        mov edi, OFFSET w43H_lit
        mov ecx, 7
        _emit 0xf3
        _emit 0xa6
        je L1
        xor eax, eax
        pop edi
        pop esi
        ret
    L1:
        mov al, BYTE PTR w43H_seqLine
        cmp al, 0x22
        je L2
    L3:
        mov al, [edx+1]
        inc edx
        cmp al, 0x22
        jne L3
    L2:
        mov cl, [edx+1]
        inc edx
        mov eax, edx
        cmp cl, 0x22
        je L5
    L6:
        mov cl, [edx+1]
        inc edx
        cmp cl, 0x22
        jne L6
    L5:
        pop edi
        mov BYTE PTR [edx], 0
        pop esi
        ret
    }
}