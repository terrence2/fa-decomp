// ?NickKey@@YAGG@Z @ rva 0x49710 (32 B) — cdecl ushort(ushort); toggles the
// ?jeffKeyOn@@3DA flag on key 0x2602. FA: mov ax,[esp+4]; cmp ax,0x2602;
// jne ret-key; cmp byte[jeffKeyOn],0; sete cl; xor ax,ax; mov [jeffKeyOn],cl;
// ret. The 80 3d cmp [mem],0 + sete plan is FA's !jeffKeyOn on a char
// (MASM-side direct mem-immediate cmp per wave-16/18), reused by plain C.
extern char jeffKeyOn;   /* ?jeffKeyOn@@3DA */

unsigned short __cdecl NickKey(unsigned short key)
{
    if (key == 0x2602) {
        jeffKeyOn = !jeffKeyOn;
        return 0;
    }
    return key;
}