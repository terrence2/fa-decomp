// v2: class gets an explicit 4-B pad so desc sits at +8 (FA lea edi,[esi+8])
// and locked at +0x74; flags via branchy if (FA: xor ecx,ecx/cmp/jne/mov ecx,1).
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
    char pad4[4];           /* FA pads desc to +8 */
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
    fl = 0;
    if (flags == 1)
        fl = 1;
    if (vt->Lock(ifp, rect, out, fl, 0) != 0)
        return 0;
    locked = 1;
    return out;
}