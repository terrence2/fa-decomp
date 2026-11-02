// _RotatedOffset@20 @ rva 0x11aa0 (48 B) — fixed-point arg shift thunk.
// FA pushes (p5, p4<<8, p3<<8, p2<<8, p2) re-reading each param from
// [esp+0x14] between pushes; the shifted copy rides EAX and the raw p2 in
// ECX (CL 4.2 plain C mirrors this: shift in ecx, raw in eax — unsteerable,
// naked asm). Calls _RotatedOffsetF24@20; ret 0x14 (stdcall both sides).
extern long __stdcall RotatedOffsetF24Q(long a1, long a2, long a3, long a4,
                                        long a5);

__declspec(naked) long __stdcall RotatedOffset(long p1, long p2, long p3,
                                               long p4, long p5)
{
    __asm {
        mov eax, [esp+14h]
        push eax
        mov eax, [esp+14h]
        shl eax, 8
        push eax
        mov eax, [esp+14h]
        mov ecx, [esp+0ch]
        shl eax, 8
        push eax
        mov eax, [esp+14h]
        shl eax, 8
        push eax
        push ecx
        call RotatedOffsetF24Q
        ret 14h
    }
}
