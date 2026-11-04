/* w35B: ?net_test_start_latency_test@@YAXH@Z @ rva 0x69eb0 (80 B)
 * NAKED-ASM v2 — CL's C route xor'd a reg for the two zero stores (89-store)
 * and DCE'd FA's dead `add eax,0x64`; MASM spells FA's shape 1:1:
 *   push ebx; push esi; esi=p; eax=plx[esi*4+66h] x3; +0x54 push + ff 15 imp;
 *   push esi; c7 imm-stores; dead add eax,64h; [eax+44h]=5; call stub(p).
 */
extern void ntst_cali(int p);       /* $FA$_t_469f00 */
extern char plx[];                  /* ?player_list@@3UNET_PLAYER_LIST@@A */
extern void *impQPF[];              /* __imp__QueryPerformanceFrequency */

void __declspec(naked) __cdecl net_test_start_latency_test(int p)
{
    __asm {
        push    ebx
        push    esi
        mov     esi, [esp+0ch]
        mov     eax, dword ptr plx[esi*4+66h]
        add     eax, 54h
        push    eax
        call    dword ptr [impQPF]
        mov     eax, dword ptr plx[esi*4+66h]
        push    esi
        mov     dword ptr [eax+64h], 0
        mov     dword ptr [eax+68h], 0
        add     eax, 64h
        mov     eax, dword ptr plx[esi*4+66h]
        mov     dword ptr [eax+44h], 5
        call    ntst_cali
        add     esp, 4
        pop     esi
        pop     ebx
        ret
    }
}