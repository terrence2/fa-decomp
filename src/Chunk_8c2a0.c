// w26a_8c2a0 @ rva 0x8c2a0 (574624, unnamed 16 B orphan) — FA bytes (raw):
//   33 c0                xor eax,eax
//   8a 41 01             mov al, [ecx+1]      (zero-extend byte load through al)
//   3b c2                cmp eax, edx
//   0f 9c c0             setl al              (result reuses the eax temp)
//   c3                   ret
//   05 00 00 00 00       (5 B census pad)
// Fastcall 2-reg-param predicate: zero-unsigned byte at p+1 vs int d.
// Wall: CL 4.2 pins the byte temp in ebx (push ebx / 33 c0 33 db / mov
// bl,[ecx+1] / cmp ebx,edx / pop ebx), 15 B — five spellings tried
// (both pointer types, local, cast, pointer arithmetic), all identical
// (register-plan class: FA reuses the eax temp for the setcc result). The
// patch rewrites the whole body to FA's 11 B eax form; CL code bytes then
// equal FA's chunk exactly.
int __fastcall w26a_8c2a0(unsigned char *p, int d)
{
    unsigned char b = p[1];
    return b < d;
}