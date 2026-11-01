// __lockerr_exit @ rva 0xd72e0 — fatal-app-exit then process exit; CL drives
//   the second dllimport call through a spare register (8b 2d / ff d5),
//   FA calls both off the IAT directly — naked asm (d177, d185)
extern void *impFAE[];
extern void *impEP[];
void __declspec(naked) lockerr_exit_q(char *msg)
{
    __asm
    {
        mov eax, dword ptr [esp+4]
        push eax
        push 0
        call dword ptr [impFAE]
        push 0xff
        call dword ptr [impEP]
        ret
    }
}
