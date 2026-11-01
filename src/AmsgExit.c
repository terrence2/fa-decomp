// __amsg_exit @ rva 0xd6230 (42 B) — int _amsg_exit(int errnum): the
// runtime-error exit path. The flag dword at __aexit_rtn+0x4
// (0x51a08c; also read by __FF_MSGBANNER/__NMSG_WRITE — the "already
// showing a message" state) gates the banner: cmp [msgFlag],1 / jne.
// C folds cmp [mem],imm into an a1 moffs load + cmp reg — naked-asm escape
// (probe w13c_amsg1 vs w13c_amsg2); msgFlag/aexit_rtn are mapped data
// anchors (interior addend +0x4 lives in the map TO only).
extern int msgFlag;
extern void __cdecl _FF_MSGBANNER(void);
extern void __cdecl _NMSG_WRITE(int errnum);
extern void *aexit_rtn[];

void __declspec(naked) _amsg_exit(void)
{
    __asm {
        cmp     dword ptr [msgFlag], 1
        jne     Lnowrite
        call    _FF_MSGBANNER
    Lnowrite:
        mov     eax, dword ptr [esp+4]
        push    eax
        call    _NMSG_WRITE
        add     esp, 4
        push    0xff
        call    dword ptr [aexit_rtn]
        add     esp, 4
        ret
    }
}