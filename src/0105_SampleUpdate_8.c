// @SampleUpdate@8 @ rva 0x12300 (80 B) — FA asm (fastcall this=ecx,
//   data=edx): push ebx/esi/edi / mov esi,[ecx+0xc] / push ebp / mov
//   edi,<_currentTicks> / lea ebx,[esi+4] / mov eax,[edx] / mov
//   ebp,[edx+4] / mov [esi],edi / mov edx,[edx+8] / mov [ebx],eax / mov
//   eax,[ecx+4] / mov [ebx+4],ebp / mov [ebx+8],edx / mov ebx,[esi+0x10] /
//   lea edx,[esi+0x10] / add eax,ebx / cmp eax,edi / jg skip / mov
//   eax,[ecx] / dec / shl 4 / push/push/push / call _memmove / add esp,0xc /
//   skip: pop ebp/edi/esi/ebx / ret.
//   Semantics: copy the 3-word {t0,t4,t8} record into sample at
//   this+0xc..+0xc+0xc with sample.t0 = currentTicks; then if
//   next-tick(this+4) <= ticks, memmove the ring (n = (count-1)<<4) from
//   sample+0x10.  Naked asm: FA's interleaved reg plan (5 live dwords across
//   the memmove pushes, ebp/ebx/esi/edi pinned) is C-unreachable in CL 4.2.
//   memmove stays a plain call (FA chunks through CRT _memmove identity).
extern long currentTicks;
extern void *__cdecl memmove(void *d, const void *s, unsigned n);

__declspec(naked) void __fastcall SampleUpdate(void *a, void *b)
{
    __asm {
        push ebx
        push esi
        push edi
        mov esi, [ecx+0xc]
        push ebp
        mov edi, dword ptr [currentTicks]
        lea ebx, [esi+4]
        mov eax, [edx]
        mov ebp, [edx+4]
        mov [esi], edi
        mov edx, [edx+8]
        mov [ebx], eax
        mov eax, [ecx+4]
        mov [ebx+4], ebp
        mov [ebx+8], edx
        mov ebx, [esi+0x10]
        lea edx, [esi+0x10]
        add eax, ebx
        cmp eax, edi
        jg Ldone
        mov eax, [ecx]
        dec eax
        shl eax, 4
        push eax
        push esi
        push edx
        call memmove
        add esp, 0xc
    Ldone:
        pop ebp
        pop edi
        pop esi
        pop ebx
        ret
    }
}