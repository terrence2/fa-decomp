/* __mbschr @ rva 0xe3c10 (181 B, CRT, FPO/esp, tail none) -- w45B v1.
 * Naked-asm transcription. MBCS lead-byte loop: fast path (no multibyte)
 * via _strchr; slow path under _lock(0x19)/_unlock(0x19) walks the string
 * testing lead bytes against __mbctype+0x1 (table flag 0x4 in dl), folds
 * the 16-bit pair into ebx (shl 8) and compares against the char; ret
 * value = esi-1 match or esi-1-if-... sbb/and epilog: (eax<=1 ? eax-1 ? ...):
 *   sub eax,edi / cmp eax,1 / sbb eax,eax / and eax,esi.
 * 16-bit bx is intra-function state (movzx/test/movzx chain), not ABI.
 * Anchors: map-renamed externs (Mbsnbcoll recipe) - the 83 3d moffs cmp
 * uses __mbctype+0x104, the test [eax+disp],dl uses __mbctype+0x1. */
extern unsigned long _w45b_mb104;   /* emits __w45b_mb104 */
extern unsigned long _w45b_mbai;    /* emits __w45b_mbai */
extern void _lock(int n);
extern void _unlock(int n);
extern void *strchr(const void *s, int c);

void __declspec(naked) _mbschr_v4(const unsigned char *s, unsigned int c)
{
    __asm {
        cmp  _w45b_mb104, 0
        push ebx
        push esi
        push edi
        jne  w45bms_slow
        mov  edi, [esp+0x14]
        mov  esi, [esp+0x10]
        push edi
        push esi
        call strchr
        add  esp, 8
        pop  edi
        pop  esi
        pop  ebx
        ret
w45bms_slow:
        push 0x19
        call _lock
        mov  esi, [esp+0x14]
        mov  edi, [esp+0x18]
        add  esp, 4
        movzx bx, byte ptr [esi]
        test bx, bx
        je   w45bms_done
        mov  edx, 4
w45bms_ld:
        /* emit xor eax,eax opaquely: CL's inline-asm tracker folds
           [eax+anchor] to [anchor] once it has tracked eax==0, giving
           84 15 instead of FA's 84 90 */
        _emit 0x33
        _emit 0xc0
        mov  al, bl
        test byte ptr _w45b_mbai[eax], dl
        je   w45bms_sb
        mov  al, [esi+1]
        inc  esi
        test al, al
        je   w45bms_null
        movzx ebx, bx
        shl  ebx, 8
        xor  ecx, ecx
        mov  cl, al
        or   ebx, ecx
        cmp  ebx, edi
        jne  w45bms_next
        push 0x19
        call _unlock
        add  esp, 4
        lea  eax, [esi-1]
        pop  edi
        pop  esi
        pop  ebx
        ret
w45bms_sb:
        movzx eax, bx
        cmp  eax, edi
        je   w45bms_done
w45bms_next:
        movzx bx, byte ptr [esi+1]
        inc  esi
        test bx, bx
        jne  w45bms_ld
        jmp  w45bms_done
w45bms_null:
        push 0x19
        call _unlock
        add  esp, 4
        xor  eax, eax
        pop  edi
        pop  esi
        pop  ebx
        ret
w45bms_done:
        push 0x19
        call _unlock
        movzx eax, bx
        add  esp, 4
        sub  eax, edi
        cmp  eax, 1
        pop  edi
        sbb  eax, eax
        and  eax, esi
        pop  esi
        pop  ebx
        ret
    }
}