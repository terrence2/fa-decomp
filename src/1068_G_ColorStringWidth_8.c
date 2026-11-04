// @G_ColorStringWidth@8 @ rva 0xb4990 — walk the color string; each char
//   indexes a 6-byte font-record row on the MMAccessR'd face, width summed in
//   edx; CL never lands sum in edx or puts the w+0x2a update BEFORE the loop
//   (probes d157/d174/d182/d189), asm exact (d191)
extern int __fastcall MMAccessR(int p1);
void __declspec(naked) __fastcall G_ColorStringWidth_q(int p1, unsigned char *s)
{
    __asm
    {
        push ebx
        push esi
        push ebp
        mov esi, edx
        call MMAccessR
        xor edx, edx
        mov cl, byte ptr [esi]
        cmp cl, dl
        je gsw3
        mov eax, dword ptr [eax+0x2a]
    gsw1:
        xor ecx, ecx
        mov cl, byte ptr [esi]
        inc esi
        lea ebx, dword ptr [ecx+ecx*2]
        mov cl, byte ptr [esi]
        movsx ebp, word ptr [eax+ebx*2+2]
        add edx, ebp
        test cl, cl
        jne gsw1
    gsw3:
        mov eax, edx
        pop ebp
        pop esi
        pop ebx
        ret
    }
}
