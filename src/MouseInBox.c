// ?MouseInBox@@YIDPAUBOX@@@Z @ rva 0xd500 (12 B + 4 pad) — push ecx / push
//   offset _shellMousePos / call _PointInBox@8 / ret.  Fastcall (YI): the BOX*
//   param arrives in ecx and is re-pushed directly as PointInBox's arg2; the
//   shell mouse position is passed by address as arg1.  char return (D in the
//   mangled name) passes through eax untouched.  Both externs identity, no maps.
extern char shellMousePos[];
extern char __stdcall PointInBox(char *pos, void *box);

struct BOX;

char __fastcall MouseInBox(struct BOX *b)
{
    return PointInBox(shellMousePos, b);
}