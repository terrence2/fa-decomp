// @StringForLanguage@8 @ rva 0x12850 (52 B + 12 pad) — copy the prefix of s up
//   to ';' (or end-of-string via @Strend@4) into d, NUL-terminated.
//   C probes (w11c_04/04b/04c) always allocate esi=ecx/edi=edx and n=ebx; FA
//   pins src->edi, dst->ebx, n->esi.  Naked asm escape reproduces FA exactly.
//   Externs _strchr/_memmove/@Strend@4 all identity, no maps.
#include <string.h>
extern char *strchr(const char *s, int c);
extern void *memmove(void *d, const void *s, size_t n);
extern char *__fastcall Strend(char *s);

void __declspec(naked) __fastcall StringForLanguage(char *s, char *d)
{
    __asm {
        push ebx
        push esi
        push edi
        mov  ebx, edx
        mov  edi, ecx
        push 0x3b
        push edi
        call strchr
        add  esp, 8
        test eax, eax
        jne  have
        mov  ecx, edi
        call Strend
    have:
        mov  esi, eax
        sub  esi, edi
        push esi
        push edi
        push ebx
        call memmove
        add  esp, 0xc
        mov  byte ptr [esi+ebx], 0
        pop  edi
        pop  esi
        pop  ebx
        ret
    }
}