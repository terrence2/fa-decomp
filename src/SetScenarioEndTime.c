extern char currentTime[];
extern char endScenarioTime[];
__declspec(naked) void __fastcall SetScenarioEndTime(unsigned short a)
{
    __asm {
        add cx, word ptr [currentTime]
        cmp word ptr [endScenarioTime], cx
        jbe fin
        mov word ptr [endScenarioTime], cx
        fin: ret
    }
}
