// ?Restore@CDirDrawSurface@@QAEHXZ @ rva 0x477700 (112 B) -- genuine C++
// thiscall member fn, w31E/w34C recipe.  COM pair:
//   r1 = iface->[0] vt +0x6c(iface), 1 arg stdcall; r1==0 -> return 1
//   dd = this+0x80; !dd -> 0
//   r2 = dd->[0] vt +0x90(dd, &idd); r2!=0 -> 0
//   Destroy(this); return Create(idd, &desc(this+0x84))
// FA: sub esp,4 / push esi prolog; 4 duplicated exits.
struct _DDSURFACEDESC { char pad[0x58]; };
struct IDirectDraw { char pad[4]; };

struct Vt1 {
    void *q[27];                       /* entry at +0x6c */
    long (__stdcall *RestoreFn)(void *);
};

struct Vt2 {
    void *q[36];                       /* entry at +0x90 */
    long (__stdcall *GetDDFn)(void *, IDirectDraw **);
};

class CDirDrawSurface {
public:
    void *iface;                       /* +0 */
    char pad[0x7c];
    void *dd;                          /* +0x80 */
    _DDSURFACEDESC desc;               /* +0x84 */
    void Destroy();
    int Create(struct IDirectDraw *, struct _DDSURFACEDESC *);
    int Restore();
};

int CDirDrawSurface::Restore()
{
    Vt1 *vt1;
    Vt2 *vt2;
    IDirectDraw *idd;

    if (iface == 0)
        return 0;
    vt1 = *(Vt1 **)iface;
    if (vt1->RestoreFn(iface) == 0)
        return 1;
    if (dd == 0)
        return 0;
    vt2 = *(Vt2 **)dd;
    if (vt2->GetDDFn(dd, &idd) != 0)
        return 0;
    Destroy();
    return Create(idd, &desc);
}