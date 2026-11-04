/* __ms_p5_test_fdiv v2: whole-body naked asm; the three [esp+0] references
 * spell _emit bytes because MASM short-forms [esp] (c7 04 24 / dd 04 24 /
 * dc 2c 24) while FA keeps the disp-0 SIB forms (c7 44 24 00 / dd 44 24 00 /
 * dc 6c 24 00). */
__declspec(naked) int __cdecl _ms_p5_test_fdiv(void)
{
    __asm {
        sub     esp, 0x18
        mov     dword ptr [esp+8], 0x80000000
        mov     dword ptr [esp+0xc], 0x4147ffff
        _emit   0xc7
        _emit   0x44
        _emit   0x24
        _emit   0x00
        _emit   0x00
        _emit   0x00
        _emit   0x00
        _emit   0xc0
        mov     dword ptr [esp+4], 0x4150017e
        _emit   0xdd
        _emit   0x44
        _emit   0x24
        _emit   0x00
        fdiv    qword ptr [esp+8]
        fmul    qword ptr [esp+8]
        _emit   0xdc
        _emit   0x6c
        _emit   0x24
        _emit   0x00
        fstp    qword ptr [esp+0x10]
        fld1
        fcomp   qword ptr [esp+0x10]
        fnstsw  ax
        test    ah, 1
        mov     eax, 1
        jne     L1
        xor     eax, eax
    L1:
        add     esp, 0x18
        ret
    }
}