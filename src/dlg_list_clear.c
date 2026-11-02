// ?dlg_list_clear@@YAXPAX@Z @ rva 0x63990 (48 B) — cdecl void(void*).
// Walks the list head (nodes linked at +0x3c) freeing each with fastcall
// MMFreePtr, then zeroes the head fields (+0,+4 dwords, +0x1c/+0x1e words,
// sets byte +0x18 = 1). Naked-asm escape after three plain-C schedules:
// CL either keeps p in ecx for the whole loop (no arg copy, next-load
// pre-call) or keeps p in esi with the next-load AFTER the call; FA wants
// p in esi, arg copy ecx=esi, next-load BETWEEN copy and call, and the
// zeroing stores in ascending offset order (xor once: [edi], [edi+4],
// word[edi+0x1c], word[edi+0x1e], byte[edi+0x18]=1) — CL shuffles them.
extern void __fastcall MMFreePtr(void *p);   /* @MMFreePtr@4 */

void __declspec(naked) __cdecl dlg_list_clear(void)
{
    __asm {
        push    esi
        push    edi
        mov     edi, [esp+0xc]
        mov     esi, [edi]
        test    esi, esi
        je      short zerof
loopf:
        mov     ecx, esi
        mov     esi, [esi+0x3c]
        call    MMFreePtr
        test    esi, esi
        jne     short loopf
zerof:
        xor     eax, eax
        mov     [edi], eax
        mov     [edi+4], eax
        mov     word ptr [edi+0x1c], ax
        mov     word ptr [edi+0x1e], ax
        mov     byte ptr [edi+0x18], 1
        pop     edi
        pop     esi
        ret
    }
}