/* w36D_65ab0_v2: whole-body naked asm (the one escape): CL from C keeps
   56 57 up-front double-save + 8b 35 modrm load + test esi vs FA's
   56 / a1 moffs / 57 / 85 c0 / bf / je / 8b f0 (mov esi,eax) seq.
   FA body 46 B, tail 8b ff 2 B pad. */
typedef unsigned long UL;

extern UL w36d_ct110;             /* __curThing+0x110 */
extern unsigned char w36d_stb[8]; /* anchor: _serviceTicks+0x28 */
extern unsigned short w36d_stw;   /* anchor: _serviceTicks+0x50 */

void __declspec(naked) w36d_65ab0(void)
{
    __asm {
        push esi
        mov eax, dword ptr [w36d_ct110]
        push edi
        test eax, eax
        mov edi, offset w36d_stb
        je Lz
        mov esi, eax
        mov ecx, 20h
        rep movsd
        pop edi
        pop esi
        ret
    Lz:
        xor eax, eax
        mov ecx, 20h
        rep stosd
        mov word ptr [w36d_stw], ax
        pop edi
        pop esi
        ret
    }
}