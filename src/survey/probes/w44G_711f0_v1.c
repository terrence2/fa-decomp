// w44G @ 0x4711f0 (rva 0x711f0, 112 B) ?MPSetControl@@YGXJGD@Z: void
// stdcall(long, ushort, char). Builds an 8-B request struct in locals
// {0x44 tag, long value @+1, ushort result @+5, char p3 @+7}, calls
// $FA$_t_46b260 (stdcall, 4 stack args: 0xffffffff, &struct, 8, 1), then
// MPFlushAll(?, 0) — FA never loads DL before the fastcall tail (pass
// whatever DL holds = unsteerable from C) => naked whole-body
// transcription. DIR32 site 04 (_numComputers); e8s: OBJAlias / ser4b /
// MPFlushAll carry mnemonic relocs. add esp,8 = own-locals cleanup.
// v1 lesson: CL spells mov BYTE PTR [esp],0x44 as the 4-B sib-no-disp
// form (c6 04 24 44); FA uses the disp8-zero form (c6 44 24 00 44) —
// that instruction is re-spelled via _emit.
extern unsigned char w44G_nc[];      /* _numComputers @0x4e7604 */
extern void __fastcall OBJAlias(long a, void *b);
extern void __fastcall MPFlushAll(unsigned long a, char b);
extern void __stdcall w44G_ser46b(long a, void *b, long c, long d);
__declspec(naked) void MPSetControl(long a, unsigned short b, char c)
{
    __asm {
        sub esp, 8
        mov eax, DWORD PTR w44G_nc
        cmp eax, 1
        je Ltail
        mov cx, WORD PTR [esp+0x10]
        mov eax, DWORD PTR [esp+0xc]
        test cx, cx
        mov DWORD PTR [esp+1], eax
        _emit 0xc6
        _emit 0x44
        _emit 0x24
        _emit 0x00
        _emit 0x44
        je Lz
        mov edx, 1
        call OBJAlias
        mov WORD PTR [esp+5], ax
        jmp Lc
    Lz:
        mov WORD PTR [esp+5], 0
    Lc:
        mov al, BYTE PTR [esp+0x14]
        push 1
        lea ecx, DWORD PTR [esp+4]
        push 8
        mov BYTE PTR [esp+0xf], al
        push ecx
        push 0xffffffff
        call w44G_ser46b
        xor ecx, ecx
        call MPFlushAll
    Ltail:
        add esp, 8
        ret 0xc
        _emit 0x8d
        _emit 0x64
        _emit 0x24
        _emit 0x00
        _emit 0x8d
        _emit 0x64
        _emit 0x24
        _emit 0x00
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
    }
}