// _MSGRemoveCurObj@0 @ rva 0x18760 (48 B) — records-walk over
// lastWeaponButton+0xf0..+0x64c8 in 0xd5 steps: mov eax,imm (b8) / loop:
// cmp word [eax+6],0xffff / je skip / mov cx,word [curId] (dis.py elided
// this line; per-iteration reload) / cmp word [eax+4],cx / jne skip /
// store 0xffff / add eax,0xd5 / cmp eax,imm (3d) / jb. Reads cx + no
// prologue — naked asm (probe w14a_msgrc2, byte-exact).
extern char msgBtnBase[];       // ?lastWeaponButton@@3DA
extern char curId[];            // word at _curId

__declspec(naked) void __stdcall MSGRemoveCurObj_q(void)
{
    __asm {
        mov eax, OFFSET msgBtnBase + 0xf0
    l1:
        cmp word ptr [eax+6], 0xffff
        je next
        mov cx, word ptr [curId]
        cmp word ptr [eax+4], cx
        jne next
        mov word ptr [eax+6], 0xffff
    next:
        add eax, 0xd5
        cmp eax, OFFSET msgBtnBase + 0x64c8
        jb l1
        ret
    }
}