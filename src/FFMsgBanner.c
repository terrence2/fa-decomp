// __FF_MSGBANNER @ rva 0xdc200 (61 B) — the runtime-error banner gate:
// banner if [__aexit_rtn+0x4]==1, or if [+4]==0 AND [+8]==1 (the second
// test is cmp dword ptr [__aexit_rtn+0x8],1 — the MASM-only mem-immediate
// cmp; dis.py ELIDED that 83 3d line in the listing, raw bytes have it).
// a1 moffs loads (C-baked field disp), then push 0xfc/0xff calls to
// __NMSG_WRITE (cdecl) around the optional indirect call of __adbgmsg
// (call eax when nonzero). Naked asm (_amsg_exit sibling precedent).
// aexit_rtn/adbgmsg are identity FA.SMS data symbols (__aexit_rtn
// 0x51a088, __adbgmsg 0x51aca8) reached via the underscored C idents.
extern void *_aexit_rtn[];                      /* symbol __aexit_rtn */
extern void *_adbgmsg[];                        /* symbol __adbgmsg */
extern void __cdecl _NMSG_WRITE(int errnum);

void __declspec(naked) _FF_MSGBANNER(void)
{
    __asm {
        mov  eax, dword ptr [_aexit_rtn + 0x4]
        cmp  eax, 1
        je   Lbanner
        test eax, eax
        jne  Ldone
        cmp  dword ptr [_aexit_rtn + 0x8], 1
        jne  Ldone
Lbanner:
        push 0xfc
        call _NMSG_WRITE
        add  esp, 4
        mov  eax, dword ptr [_adbgmsg]
        test eax, eax
        je   Lskip
        call eax
Lskip:
        push 0xff
        call _NMSG_WRITE
        add  esp, 4
Ldone:
        ret
    }
}