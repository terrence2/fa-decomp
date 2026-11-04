// __unlock_fhandle @ rva 0xdee10 (40 B) — drop the per-handle CRT critical
// section: p = table[(fh>>5) as byte-offset] (the pointer table lives at
// 0x588c70 = __crtheap+4; FA indexes it BY BYTE OFFSET, [eax+disp], after
// and ~0x18 / sar 3), then p += (fh&31)*36 + 12 (36 = 4*9 lea chain), and
// LeaveCriticalSection(p) off the IAT. C loses two battles here — group/idx
// reg order (FA keeps grp in eax, idx in ecx) and the dead push/pop ebx
// wrap on the dllimport call — so naked asm (probe w13c_unlfh1 C attempt,
// w13c_unlfh3 exact; fhLockBase[eax] bracket-after-symbol form forces the
// 8b 80 sib-less load, the [eax+sym] spelling is dropped to an a1 moffs).
extern char fhLockBase[];
extern void *impLeaveCS[];

void __declspec(naked) _unlock_fhandle(void)
{
    __asm {
        mov     ecx, dword ptr [esp+4]
        mov     eax, ecx
        and     ecx, 0x1f
        shl     ecx, 2
        and     eax, 0xffffffe7
        sar     eax, 3
        lea     edx, dword ptr [ecx+ecx*8]
        mov     eax, dword ptr fhLockBase[eax]
        add     eax, edx
        add     eax, 0xc
        push    eax
        call    dword ptr [impLeaveCS]
        ret
    }
}