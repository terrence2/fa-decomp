// ?verifyPacketCRC@@YADAAUSERIAL_PACKET@@@Z @ rva 0x98070 (48 B) —
//   push esi/edi; esi = param ([esp+0xc]); computePacketCRC -> edi,
//   packetCRC -> eax, cmp edi,eax (3b f8 — CL plain-C emitted the mirror
//   3b c7 cmp eax,edi: 1-byte mismatch, probe 1), sete cl / mov al,cl
//   (CL's sete-al plan differs), pop/pop/ret. asm escape pins the cmp
//   operand order and the sete cl/mov al,cl double-move.
extern unsigned long computePacketCRC(void *p);
extern unsigned long packetCRC(void *p);

__declspec(naked) char verifyPacketCRC(void)
{
    __asm {
        push    esi
        push    edi
        mov     esi, dword ptr [esp+0xc]
        push    esi
        call    computePacketCRC
        add     esp, 4
        mov     edi, eax
        push    esi
        call    packetCRC
        add     esp, 4
        cmp     edi, eax
        sete    cl
        mov     al, cl
        pop     edi
        pop     esi
        ret
    }
}