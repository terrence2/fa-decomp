// _PreferredProtectId@0 @ rva 0x636e0 (48 B) — ushort return; dword flags
// at _curThing+0xf0 re-read at every guard: bit30 clear -> xor ax,ax/ret;
// bit31 set -> mov ecx,eax and tail-jmp the fastcall helper (unnamed
// chunk 0x45dc60, $FA$_t_ target per wave-13 rule — layout.json name is
// None); bit31 clear -> mov ax,word [re-read] (66 a1) / ret.
// C always evaluates the second read straight into the fastcall arg reg
// (8b 0d + f7 c1, w14a_ppi1/2/3) — naked asm (w14a_ppi4, byte-exact; MASM
// emits the a9 accumulator form for test eax,imm).
extern char curThing[];
extern unsigned short __fastcall PrefHelper_q(unsigned long f);

__declspec(naked) unsigned short PreferredProtectId_q(void)
{
    __asm {
        mov eax, dword ptr [curThing+0xf0]
        test eax, 0x40000000
        jne l2
        xor ax, ax
        ret
    l2:
        mov eax, dword ptr [curThing+0xf0]
        test eax, 0x80000000
        je l3
        mov ecx, eax
        jmp PrefHelper_q
    l3:
        mov ax, word ptr [curThing+0xf0]
        ret
    }
}