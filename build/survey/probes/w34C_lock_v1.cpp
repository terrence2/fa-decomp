// ?Lock@CDirDrawSurface@@QAEPAU_DDSURFACEDESC@@PAUtagRECT@@H@Z
// @ rva 0x77770 (489328, 96 B) — genuine C++ thiscall (w31E SP precedent).
// if (!iface) return 0; if (locked==1) return 0;
// fl = (flags==1); COM call vx->Lock(iface, rect, this+8, fl, 0) via
// mov ebx,[edx] / call [ebx+0x64]; success (eax==0): locked=1, return this+8;
// else 0.
struct _DDSURFACEDESC { char pad[0x6c]; };
struct tagRECT { char pad[0x10]; };

struct DDIFVt {
    void *q[25];   /* 25 entries = 0x64 B */
    unsigned char (__stdcall *Lock)(void *iface, tagRECT *r,
                                    _DDSURFACEDESC *out, unsigned long fl,
                                    unsigned long ev);
};

class CDirDrawSurface {
public:
    void *iface;            /* +0 COM object ptr */
    _DDSURFACEDESC desc;    /* +8 out buffer */
    long locked;            /* +0x74 */
    _DDSURFACEDESC *Lock(tagRECT *rect, int flags);
};

_DDSURFACEDESC *CDirDrawSurface::Lock(tagRECT *rect, int flags)
{
    unsigned long *ifp;
    DDIFVt *vt;
    _DDSURFACEDESC *out;
    unsigned long fl;

    ifp = (unsigned long *)iface;
    if (ifp == 0)
        return 0;
    if (locked == 1)
        return 0;
    vt = *(DDIFVt **)ifp;
    out = &desc;
    fl = (flags == 1);
    if (vt->Lock(ifp, rect, out, fl, 0) != 0)
        return 0;
    locked = 1;
    return out;
}