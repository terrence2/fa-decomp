// _APGetPark@0 @ rva 0xb9770 (80 B) — int APGetPark(void) __stdcall:
// c = *(char**)(_curThing+0x231); if (!c) return -1; walk the word array at
// c+0x111 (a1 + 8b 0d moffs re-read of the global — FA re-reads, CL
// caches), count = *(short*)(c+0xe0); i = 0; if ((short)count <= i)
// return -1; then loop comparing *(unsigned short*)walk == curId (word
// load hoisted inside the loop against cx, bound reloaded via
// movsx ecx,dx). FA's mixed-width bound checks (cmp dx,ax pre, 32-bit
// movsx in-loop) and the inside-loop curId reload are asm-only.
extern int curThing231;              /* dword at _curThing+0x231 */
extern unsigned short curId;

int __declspec(naked) __stdcall APGetParkQ(void)
{
    __asm {
        push esi
        mov  eax, dword ptr [curThing231]
        test eax, eax
        jne  hasThing
        mov  eax, -1
        pop  esi
        ret
    hasThing:
        xor  eax, eax
        mov  ecx, dword ptr [curThing231]
        mov  dx, word ptr [ecx+0xe0]
        cmp  dx, ax
        jle  fail
        lea  esi, [ecx+0x111]
    walk:
        mov  cx, word ptr [curId]
        cmp  word ptr [esi], cx
        je   found
        add  esi, 2
        inc  eax
        movsx ecx, dx
        cmp  ecx, eax
        jg   walk
    fail:
        mov  eax, -1
    found:
        pop  esi
        ret
    }
}