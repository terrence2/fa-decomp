// Transplant husk (whole-body patch) for ?MPGraphicAddSpecialDebris@@YGXPAUF24_POINT3@@GD@Z,
// rva 457648 (0x6fbb0), 112 B.
// FA semantics (dis.py 0x6fbb0): stdcall(F24_POINT3 *pt, unsigned short g, char c):
//   if (_numComputers == 1) return;                       // a1 0476 4e00; cmp 1
//   pack unsigned char debris[12] = {pt->x,pt->y,pt->z, g==0?0:OBJAlias(1,g), c};
//     (movzx/66 ops, struct at esp+4..esp+0x10 pack(1))
//   $FA$_t_46b260(debris, 12, 1, -1);                      // cdecl 4-arg stub (ret 0x10 tail)
//   ret 0xc                                                // FA double-clean quirk: callee also
//                                                          // cleans; __cdecl spelling
// CL cannot match the pack(1) 12-B struct schedule; body fully patched over husk.
struct F24_POINT3 { long a; };
void __stdcall MPGraphicAddSpecialDebris(F24_POINT3 *p, unsigned short g, char c)
{ (void)p; }