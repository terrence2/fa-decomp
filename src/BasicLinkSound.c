// @BasicLinkSound@8 @ rva 0x33120 (80 B) — FA asm (fastcall s=ecx, x=edx):
//   push esi / push edx (arg15) / six imm pushes (arg14..arg8) / xor eax /
//   mov ax,<radioVol> (66 a1) / push -1/-1 / mov edx,eax / shl eax,8 / push
//   0/0 / sub eax,edx / cdq / mov esi,0x64 / idiv esi / push eax / push
//   0xff / push ecx (arg1=s) / call ?SoundOn@@YGFPADFFDGFFDFFGGFEF@Z (the
//   15-arg stdcall; callee cleans, so ret follows the call) / pop esi / ret.
//   vol% = radioVol*0xff/100 pushed as arg3.  Naked asm: FA interleaves the
//   vol computation amid the push sequence and computes the div between
//   pushes (ButtonSound class, wave-11) — no C form reproduces that push/
//   compute interleave; the edx/param passthrough at entry confirms naked.
//   BasicSound (rva 0x330f0) is the 14-id twin that tail-jmps; here the call/
//   ret shape stays a full call.
extern unsigned short radioVol;
extern char __stdcall SoundOn(char *s, int a1, int a2, int a3, int a4,
                              int a5, int a6, int a7, int a8, int a9,
                              int a10, int a11, int a12, int a13, int a14);

__declspec(naked) char __fastcall BasicLinkSound_q(char *s, int x)
{
    __asm {
        push esi
        push edx
        push 0
        push 0
        push 0ffffh
        push 0ffffh
        push -1
        push 0
        push 0
        xor eax, eax
        mov ax, word ptr [radioVol]
        push -1
        push -1
        mov edx, eax
        shl eax, 8
        push 0
        push 0
        sub eax, edx
        cdq
        mov esi, 64h
        idiv esi
        push eax
        push 0ffh
        push ecx
        call SoundOn
        pop esi
        ret
    }
}