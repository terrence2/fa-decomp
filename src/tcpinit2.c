// ?tcpinit2@@YADPAUNET_PROTOCOL@@PAUCN_INFO@@@Z @ rva 0xa8c00 (32 B) — FA asm:
//   mov eax,[esp+4] / mov ecx,[esp+8] / push ecx / push eax / mov [eax+0xb],1 /
//   call tcp_save_settings / add esp,8 / mov al,1 / ret. Plain C: the callee is
//   cdecl so CL pushes both params early (push ecx/push eax right-to-left) and
//   interleaves the byte store between the pushes and the call — store-before-
//   call source order gives exactly that; return 1 is b0 01.
extern void __cdecl tcpSaveSettingsX(void *proto, void *cn);

char tcpinit2(void *proto, void *cn)
{
    *(char *)((char *)proto + 0xb) = 1;
    tcpSaveSettingsX(proto, cn);
    return 1;
}