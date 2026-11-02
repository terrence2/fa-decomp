// __validdrive v4 — naked asm escape: CL's C kept repurposing the param
// slot for buf (stores at [esp+4..7]) plus a nop+push-ebx/pop-ebx dance
// around the early return (v1-v3, 81 B vs FA's 76 B, buf at [esp+0], no
// ebx).  Byte-for-byte from FA rva 0xd5420:
//   8b442404 / 83ec04 / 85c0 / 7509 (d==0 -> ret 1) / b801000000 / 83c404 /
//   c3 / c6442401 3a / c6442402 5c / c6442403 00 / 0440 (add al,0x40) /
//   88442400 / 8d442400 / 50 / ff1514a65800 (IAT) / 85c0 / 740e / 83f801 /
//   7409 / b801000000 / 83c404 / c3 / 33c0 / 83c404 / c3
__declspec(dllimport) unsigned int __stdcall GetDriveTypeA(const char *root);
/* map __imp__GetDriveTypeA@4=__imp__GetDriveTypeA */

__declspec(naked) int __cdecl w25c_validdrive_q(unsigned int drive)
{
    __asm {
        mov eax, DWORD PTR [esp + 4]
        sub  esp, 4
        test eax, eax
        jne  L_have
        mov  eax, 1
        add  esp, 4
        ret
    L_have:
        mov  BYTE PTR [esp + 1], 0x3a
        mov  BYTE PTR [esp + 2], 0x5c
        mov  BYTE PTR [esp + 3], 0
        add  al, 0x40
        mov  BYTE PTR [esp], al
        lea  eax, DWORD PTR [esp]
        push eax
        call GetDriveTypeA
        test eax, eax
        je   L_zero
        cmp  eax, 1
        je   L_zero
        mov  eax, 1
        add  esp, 4
        ret
    L_zero:
        xor  eax, eax
        add  esp, 4
        ret
    }
}