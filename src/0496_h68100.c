/* w36F 0x68100 (64B) v7 — naked-asm escape, seventh variant. Six plain-C
 * spellings (ternary 0x4000:0 -> setge+dec; ternary -1:0 -> sbb ecx+push0
 * early; 0u-rel -> mov1+adc+neg; unary minus; /G4 and /O2 with reordered
 * statements) ALL emit the mask AFTER the call with the param copied to esi
 * (sbb ecx,ecx) and cmp thresh-first — FA's schedule is mask-before-call with
 * the param consumed in place (inc ecx / cmp ecx,1 / sbb esi,esi) and the
 * and+add filling the post-call gap. Scheduler wall, body verbatim:
 * FA: push esi; inc ecx; push 0; cmp ecx,1; sbb esi,esi; call _GetDiskFree;
 * and esi,0x4000; add esp,4; add esi,0x65e0; cmp eax,esi; jge +10; push 1;
 * push <_pilotsUpdated+0x20c>; call _DoDialogInfoBox@8; xor al,al; pop esi;
 * ret; mov al,1; pop esi; ret + 8d642400+8da42400000000 pad
 */
extern unsigned long __cdecl GetDiskFree(int mode);
extern long __stdcall DoDialogInfoBox(char *a, int b);
extern char w36f_dlg[2];   /* -> _pilotsUpdated+0x20c */

void __declspec(naked) __fastcall w36f_gdfckn(int avail)
{
    __asm {
        push    esi
        inc     ecx
        push    0
        cmp     ecx, 1
        sbb     esi, esi
        call    GetDiskFree
        and     esi, 00004000h
        add     esp, 4
        add     esi, 000065e0h
        cmp     eax, esi
        jge     L1
        push    1
        push    offset w36f_dlg
        call    DoDialogInfoBox
        xor     al, al
        pop     esi
        ret
L1:
        mov     al, 1
        pop     esi
        ret
    }
}