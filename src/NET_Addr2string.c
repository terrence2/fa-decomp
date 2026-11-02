// ?NET_Addr2string@@YADPAUNET_ADDRESS@@PAD@Z @ rva 0xad7f0 (32 B) — void
// NET_Addr2string(UNET_ADDRESS *addr, char *buf): dispatch through
// proto_ptr's slot at +0x62 (call [ebx+0x62]; proto_ptr reloaded into ebx
// AFTER arg pushes). __cdecl (bare ret — caller cleans). Naked asm escape:
// FA's plan loads param2 into eax / param1 into ecx and picks ebx for the
// table base — unsteerable from plain C (probe-free: ebx reg choice).
extern void *proto_ptr;

void __declspec(naked) __cdecl netAddr2stringQ(void)
{
    __asm {
        mov  eax, dword ptr [esp+0x8]
        push ebx
        mov  ecx, dword ptr [esp+0x8]
        push eax
        push ecx
        mov  ebx, dword ptr [proto_ptr]
        call dword ptr [ebx+0x62]
        add  esp, 0x8
        pop  ebx
        ret
    }
}