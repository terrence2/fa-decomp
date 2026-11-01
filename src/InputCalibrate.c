// _InputCalibrate @ rva 0x175e0 (48 B) — FA asm: movsx eax,[esp+4] (short
//   param) / push 1 / call dword ptr [deviceProcs + eax*4] (ff 14 85) / add
//   esp,4 / cmp word <mouseShown>,0 / jg done / loop: call
//   ?ShellShowMouse@@YGXXZ / cmp word <mouseShown>,0 / jle loop / done: ret.
//   Naked asm: FA's indirect call goes straight through the sib-4 table
//   (ff 14 85 <deviceProcs>); CL's C form loads the pointer into a reg and
//   calls (ff d0), and the wait-loop re-tests at the bottom (do-while
//   re-entry after the entry-only test, wave-8 loop-head rule).
typedef short (__cdecl *DEVPROC)(short a, short b);
extern DEVPROC deviceProcs[];
extern short mouseShown;
extern void __stdcall ShellShowMouse(void);

__declspec(naked) void InputCalibrate(short v)
{
    __asm {
        movsx eax, word ptr [esp+4]
        push 1
        call dword ptr deviceProcs[eax*4]
        add esp, 4
        cmp word ptr mouseShown, 0
        jg Ldone
    Lwait:
        call ShellShowMouse
        cmp word ptr mouseShown, 0
        jle Lwait
    Ldone:
        ret
    }
}