// _GG_SetPalette@16 @ rva 0x5d4a0 = 382112, 80 B.
//   thiscall: mov ecx,[globalPrimarySurface]; test; je end; mov eax,[mode];
//   cmp 0x100/0x200/0x400 je end; stage p4..p1 right-to-left with p1 pulled
//   last through eax; call ?SetEntries@CDirDrawSurface@@QAEHPAUT_RGB@@JJD@Z;
//   pop ebx; ret 0x10.
extern "C" {
void *globalPrimarySurfaceQ;  /* map _globalPrimarySurfaceQ=_globalPrimarySurface */
long _spModeQ;                /* map __spModeQ=_tempYLR+0x4e70 */
}

union T_RGB;

class CDirDrawSurface {
public:
    int SetEntries(union T_RGB *, long, long, char);
};

extern "C" void __stdcall GG_SetPaletteQ(union T_RGB *ent, long a, long b, char c)
{
    CDirDrawSurface *s;
    s = (CDirDrawSurface *)globalPrimarySurfaceQ;
    if (s != 0 && _spModeQ != 0x100 && _spModeQ != 0x200 && _spModeQ != 0x400)
        s->SetEntries(ent, a, b, c);
}