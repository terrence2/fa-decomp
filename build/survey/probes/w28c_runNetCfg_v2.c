// 0x5bb0 — v2 switch dictation
extern void __cdecl w28c_cfgScreen(long state, void (__cdecl *fn)(char *a, char *b));
extern void __cdecl w28c_ipxOpt(char *a, char *b);
extern void __cdecl w28c_tcpOpt(char *a, char *b);

void __stdcall w28c_runNetCfgScr(long state)
{
    switch (state) {
    case 1: w28c_cfgScreen(state, w28c_ipxOpt); break;
    case 4: w28c_cfgScreen(state, w28c_tcpOpt); break;
    }
}
