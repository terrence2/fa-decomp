// ?Lock@CDirDraw@@QAEPAU_DDSURFACEDESC@@PAVCDirDrawSurface@@PAUtagRECT@@H@Z
// @ rva 0x1dd40 (32 B) — thiscall trampoline: this unused; FA:
// eax=[esp+0xc](flag); ecx=[esp+8](rect); push ea/ec; ecx=[esp+0xc](surf);
// call ?Lock@CDirDrawSurface@@...; ret 0xc. C++ member so CL emits the QAEPAC
// mangle; inner member call resolves to the FA chunk symbol (pass-through).
struct _DDSURFACEDESC;
struct tagRECT;
class CDirDrawSurface {
public:
    struct _DDSURFACEDESC * Lock(struct tagRECT *rect, int flag);
};
class CDirDraw {
public:
    struct _DDSURFACEDESC * Lock(CDirDrawSurface *surf, struct tagRECT *rect,
                                 int flag);
};

struct _DDSURFACEDESC * CDirDraw::Lock(CDirDrawSurface *surf,
                                       struct tagRECT *rect, int flag)
{
    return surf->Lock(rect, flag);
}
