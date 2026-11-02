// ?net_set_ready@@YAXPAUsocket_state@@@Z @ rva 0xae110 (32 B) — reads the
//   player id at socket_state+0, indexes the UNET_PLAYER_LIST slot array
//   at player_list+0x66 (mov edx,[tab+ecx*4], sib-8d), sets the player
//   record byte +0x37 = 1 (c6 42 37 01 direct store — dis.py elides these,
//   objdump cross-checked), then inc dword player_list+8. Both disp32s
//   carry fixups -> symbol refs. asm escape: FA plans param load into eax
//   BEFORE the push ebx (cbProlog=5 quirk) and the sib-8d indexed moffs —
//   naked asm pins both; CL would push ebx first and re-read [esp+8].
extern void *netPlayerArr[];
extern unsigned long netReadyCnt;

void __declspec(naked) _net_set_ready(void)
{
    __asm {
        mov     eax, dword ptr [esp+4]
        push    ebx
        mov     ecx, dword ptr [eax]
        mov     edx, dword ptr netPlayerArr[ecx*4]
        mov     byte ptr [edx+0x37], 1
        inc     dword ptr netReadyCnt
        pop     ebx
        ret
    }
}