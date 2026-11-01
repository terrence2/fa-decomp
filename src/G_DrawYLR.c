// @G_DrawYLR@4 @ rva 0x96510 — walk 6-byte {y2,y1,x2} triples drawing one
//   horizontal line each until the 0x80 stop flag; loop head sits at the
//   movsx block (entry test uses the param's ecx once), two test sites with
//   different bases force asm (d151-d173 reg-cache in ebx), d190 exact
extern int __stdcall G_UHline(int a, int b, int c);
void __declspec(naked) __fastcall G_DrawYLR_q(int rec)
{
    __asm
    {
        push esi
        mov esi, ecx
        test byte ptr [ecx+1], 0x80
        jne gylr3
    gylr1:
        movsx eax, word ptr [esi]
        movsx ecx, word ptr [esi+4]
        movsx edx, word ptr [esi+2]
        push eax
        add esi, 6
        push ecx
        push edx
        call G_UHline
    gylr2:
        test byte ptr [esi+1], 0x80
        je gylr1
    gylr3:
        pop esi
        ret
    }
}
