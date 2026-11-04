/* ExpandSB @ rva 824120 dec (0xc9338, 89 B, gap chunk, no FPO) — 8-bit
 * sound-buffer expansion: per loop pass reads 2 bytes, expands each to a
 * 16-bit word (bh = bl, then the word duplicated into a dword via the
 * push dx / mov dx,bx / shl ebx,16 / mov bx,dx / pop dx dance) and
 * writes the two dwords interleaved (w1, w2, w1, w2) — 4 dword stores
 * per iteration, 0x200 iterations. Sibling of src/ExpandDB.c (wave-25
 * naked-asm recipe): pusha / 16-bit pushes / the dec cx + jne loop tail
 * are _emit'd raw — CL 4.2 inline-asm cannot spell them. No relocations
 * in the chunk (sites preview empty). Section name = chunk _ExpandSB
 * defines the FA public. */
void __declspec(naked) __cdecl ExpandSBZ(unsigned char *s, unsigned int *d)
{
    __asm {
        push ebp
        mov ebp, esp
        _emit 0x60
        mov eax, [ebp + 8]
        mov edx, [ebp + 0xc]
        _emit 0x66
        _emit 0x51
        push ebx
        _emit 0x66
        _emit 0xb9
        _emit 0x00
        _emit 0x02
expand_loop:
        mov bl, [eax]
        mov bh, bl
        push dx
        mov dx, bx
        shl ebx, 0x10
        mov bx, dx
        pop dx
        mov [edx], ebx
        add edx, 4
        push ebx
        inc eax
        mov bl, [eax]
        mov bh, bl
        push dx
        mov dx, bx
        shl ebx, 0x10
        mov bx, dx
        pop dx
        mov [edx], ebx
        add edx, 4
        mov esi, ebx
        pop ebx
        mov [edx], ebx
        add edx, 4
        mov ebx, esi
        mov [edx], ebx
        add edx, 4
        inc eax
        _emit 0x66
        _emit 0x49
        _emit 0x75
        _emit 0xbe
        _emit 0x5b
        _emit 0x66
        _emit 0x59
        _emit 0x61
        pop ebp
        ret
    }
}