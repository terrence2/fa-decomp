// _GG_SetPalette@16 @ rva 0x5d4a0 = 382112, 80 B. v2: T_RGB declared as a
// STRUCT (FA mangle PAUT_RGB@@ = U-tag = struct; my v1 'union' emitted
// PAT_RGB@@ and missed).
extern "C" {
void *globalPrimarySurfaceQ;
long _spModeQ;
}

struct T_RGB;

class CDirDrawSurface {
public:
    int SetEntries(struct T_RGB *, long, long, char);
};

extern "C" void __stdcall GG_SetPaletteQ(struct T_RGB *ent, long a, long b, char c)
{
    CDirDrawSurface *s;
    s = (CDirDrawSurface *)globalPrimarySurfaceQ;
    if (s != 0 && _spModeQ != 0x100 && _spModeQ != 0x200 && _spModeQ != 0x400)
        s->SetEntries(ent, a, b, c);
}