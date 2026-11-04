/* w36B v1: ?GetHandle16@@YIFPAX@Z rva 0xa9cb0 (96 B).
 * Whole-body naked-asm: FA's ABI passes the 16-bit handle count in DI
 * (mov di, openHandles at entry; no stack param read — FPO params=0) and
 * the handle value in ECX; the search loop walks handles32[0..0x10) in ax.
 * Success: inc di, openHandles=di, handles32[sx(ax)]=ecx, return ax.
 * Miss (>=16 or no free slot): return 0xffff.  Naked + CL's own prologue
 * is not usable (FA's prologue is just push ebx/esi/edi, part of the body
 * below), so everything incl. prologue/epilogue lives in the asm block.
 * C signature (short, void*) mirrors the @@YIFPAX@Z mangling.
 */
extern unsigned short openHandles;
extern void *handles32[];

unsigned __declspec(naked) __cdecl GetHandle16(short a1, void *a2)
{
    __asm {
        push ebx
        push esi
        push edi
        mov di, openHandles
        cmp di, 10h
        jl L2
        mov ax, 0ffffh
        pop edi
        pop esi
        pop ebx
        ret
L2:     xor ax, ax
        xor edx, edx
Lfind:  movsx esi, ax
        mov ebx, handles32[esi*4]
        test ebx, ebx
        je L3
        inc ax
        cmp ax, 10h
        jl Lfind
        mov ax, 0ffffh
        pop edi
        pop esi
        pop ebx
        ret
L3:     inc di
        movsx edx, ax
        mov openHandles, di
        mov handles32[edx*4], ecx
        pop edi
        pop esi
        pop ebx
        ret
    }
}