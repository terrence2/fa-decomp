// 0x5bb0 ?RunNetConfigurationScreen@@YGXJ@Z (64 B) — v1
extern void __cdecl w28c_cfgScreen(long state, void (__cdecl *fn)(char *a, char *b));
extern void __cdecl w28c_ipxOpt(char *a, char *b);
extern void __cdecl w28c_tcpOpt(char *a, char *b);

void __stdcall w28c_runNetCfgScr(long state)
{
    if (state == 1) { w28c_cfgScreen(state, w28c_ipxOpt); return; }
    if (state == 4) { w28c_cfgScreen(state, w28c_tcpOpt); return; }
}
