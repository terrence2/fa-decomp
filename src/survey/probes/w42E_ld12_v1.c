/* w42E candidate 2: __ld12told @ rva 0xdfd20 (916768, 129 B) — LONGDBL.ASM
 * (asm-source CRT): 12-byte LD -> 10-byte LD. 16-bit exp/sign regs (si/di),
 * hand-built 3-dword mantissa buffer interleaved INTO the arg-push gap of the
 * __RoundMan(&buf, 0x40) call, round-carry side effect buf[0]=0x80000000.
 * Interleaved pushes are out of reach for C scheduling; asm verbatim.
 */
extern long __cdecl _RoundMan(long *buf, long bits);

void __declspec(naked) __cdecl _ld12told(void *src, void *dst)
{
    __asm {
        mov  ecx, [esp+4]                 ; arg1 = 12-B LD source
        sub  esp, 0xc
        push ebx
        push esi
        push edi
        xor  ebx, ebx
        mov  di, word ptr [ecx+0ah]       ; exp word
        mov  eax, [ecx+6]                 ; mantissa dword 2
        mov  si, di
        mov  edx, [ecx+2]                 ; mantissa dword 1
        and  si, 0x7fff
        mov  [esp+0ch], eax               ; buf[0] = man2
        and  di, 0x8000                   ; sign
        xor  eax, eax
        mov  ax, word ptr [ecx]           ; mantissa word 0
        push 0x40
        shl  eax, 0x10
        lea  ecx, [esp+10h]               ; &buf[0]
        mov  [esp+14h], edx               ; buf[1] = man1
        push ecx
        mov  [esp+1ch], eax               ; buf[2] = w0 << 16
        call _RoundMan
        add  esp, 8
        test eax, eax
        je   Lnoround
        mov  dword ptr [esp+0ch], 0x80000000
        inc  si
Lnoround:
        cmp  si, 0x7fff
        jne  Lnoover
        mov  ebx, 0x1
Lnoover:
        or   di, si
        mov  eax, [esp+0ch]
        mov  ecx, [esp+20h]               ; arg2 = 10-B LD dest
        mov  edx, [esp+10h]
        mov  [ecx+8], di
        mov  [ecx+4], eax
        mov  eax, ebx
        pop  edi
        pop  esi
        mov  [ecx], edx
        pop  ebx
        add  esp, 0ch
        ret
    }
}