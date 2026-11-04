// @ObjPlusAngleParm@8 @ rva 0x62d80 (21 B) — two fastcall word params stored to
//   a 4-byte local (lo/hi) that is then re-read as a dword for the return;
//   4-byte struct return in eax reproduces mov [esp],cx / [esp+2],dx.
typedef struct { short x; short y; } SP2;
SP2 __fastcall ObjPlusAngleParm_q(short a, short b)
{
    SP2 t;
    t.x = a;
    t.y = b;
    return t;
}
