// _CTEval_twr @ rva 0x64640 (16 B) — jmp _COTwr@0
extern long __stdcall COTwr(void);

long __cdecl CTEval_twr(void)
{
    return COTwr();
}
