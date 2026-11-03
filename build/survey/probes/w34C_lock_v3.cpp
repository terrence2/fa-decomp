// v3: FA's statement order is fl-scan BEFORE out-lea and before the vt load:
//   33 c9 (fl=0, ecx) | mov eax,[esp+14] flags | cmp | jne | mov ecx,1 |
//   lea edi,[esi+8] (out) | push 0 | ... call prep ... | mov ebx,[edx] (vt)
//   inside the push sequence.  COM stub returns long in the FA code
//   (85 c0 test eax,eax after the call, while v2 emitted 84 c0 for an
//   unsigned-char stub).  Drop the named `out` local; use &desc directly.
struct _DDSURFACEDESC { char pad[0x6c]; };
struct tagRECT { char pad[0x10]; };

struct DDIFVt {
    void *q[25];   /* 25 entries = 0x64 B */
    long (__stdcall *Lock)(void *iface, tagRECT *r,
                           _DDSURFACEDESC *out, long fl,
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
    long fl;

    ifp = (unsigned long *)iface;
    if (ifp == 0)
        return 0;
    if (locked == 1)
        return 0;
    vt = *(DDIFVt **)ifp;
    fl = 0;
    if (flags == 1)
        fl = 1;
    if (vt->Lock(ifp, rect, &desc, fl, 0) != 0)
        return 0;
    locked = 1;
    return &desc;
}