/* w46B_blit_v1 - ?Blit@CDirDrawSurface@@QAEJPAUtagRECT@@PAUIDirectDrawSurface@@0K@Z
 * FA rva 0x77810 (489488), 160 B, tail 8d4900 (3 B census pad). ZERO FA .reloc sites
 * (all COM vtable dispatch, no globals) — whole-chunk transplant of FA bytes; husk
 * documents semantics (vtable call sites verified: [eax+0x14] Blt slot, [ebx+0x2c]).
 *
 * FA anatomy (thiscall QAE, J ret, FPO esp, locals=0, cbRegs=2 ebx/esi, ret 0x10):
 *   push ebx; push esi; mov edx,[ecx] (ths->dds[0]); mov esi,ecx; test edx -> E_FAIL 0x80004005 x3:
 *   guard1: if (ths->dds[0]==0) ret E_FAIL
 *   guard2: if (arg2 srcDD == 0) ret E_FAIL
 *   guard3: if (ths->_74 == 1)  ret E_FAIL
 *   if (ths->bF4 == 1) { guard4: if (ths->dds[4]==0) ret E_FAIL;
 *        receiver = ths->dds[4]; blit-args block (duplicated by FA's compiler); }
 *   else receiver = ths->dds[0];
 *   blit block: eax=[esp+0x18] (arg4 flags); push 0 (NULL DDBLTFX);
 *     ebx=[esp+0x18] (arg3 dstRect); push eax; push ebx; eax=[receiver] vtable;
 *     push ecx (arg2 srcDD); ecx=[esp+0x1c] (arg1 srcRect); push ecx; push receiver;
 *     call [vtable+0x14]  —  Blt(srcRect, srcDD, dstRect, flags, NULL) on receiver DDS
 *   if hr!=0 => pop esi/ebx; ret 0x10 (return hr)
 *   success path: eax=[esi] (obj[0]); push 1; ebx=[eax] vtable; push 0; push eax;
 *     call [ebx+0x2c] (GetDC-like slot 11: hwnd=1?/flags 0/1); pop esi/ebx; ret 0x10
 */
#define NULL ((void *)0)
typedef struct { void *dds0, *dds4; unsigned char pad8[0x74-0x8]; long _74; unsigned char pad78[0xf4-0x78]; char bF4; } CDDS;
typedef long (*VT14)(void *recv, void *srcRect, void *srcDD, void *dstRect, unsigned long flags);   /* vtable +0x14 (Blt slot) */
typedef long (*VT2C)(void *recv, void *a2, void *a3);   /* vtable +0x2c (slot 11) */

long Blit(CDDS *ths, void *srcRect, void *srcDD, void *dstRect,
          unsigned long flags)  /* thiscall: FA passes via ecx; transplant */
{
    long hr;
    void *recv;
    void *vt;
    if (ths->dds0 == NULL) return 0x80004005;
    if (srcDD == NULL)      return 0x80004005;
    if (ths->_74 == 1)     return 0x80004005;
    if (ths->bF4 == 1)
    {
        if (ths->dds4 == NULL) return 0x80004005;
        recv = ths->dds4;
    }
    else
        recv = ths->dds0;
    vt = *(void **)recv;
    hr = ((VT14 *)vt)[5](recv, srcRect, srcDD, dstRect, flags);
    if (hr != 0)
        return hr;
    return ((VT2C *)vt)[11](ths->dds0, NULL, NULL);
}