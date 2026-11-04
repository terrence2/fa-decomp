// ?DestroySurface@CDirDraw@@QAEHPAVCDirDrawSurface@@@Z @ rva 0x1db90 (48 B) —
// __thiscall member (this unused). FA: push esi; esi=[esp+8](surf);
// test esi,esi / jne; xor eax,eax; pop esi; ret 4 (NULL -> 0);
// mov ecx,esi / call $FA$_t_4779a0 (jmp-thunk to CDirDrawSurface::Destroy,
// fastcall-this shape); push esi / call $FA$_t_4d4880 (cdecl free wrapper);
// add esp,4; mov eax,1; pop esi; ret 4. First thiscall-band member written
// as C++ (CL 4.2 emits the exact QAEH mangle for an out-of-line definition).
class CDirDrawSurface;
class CDirDraw {
public:
    int DestroySurface(CDirDrawSurface *surf);
};

extern "C" void __fastcall dsurfDestroyQ(void *surf);   /* $FA$_t_4779a0 */
extern "C" void __cdecl dsurfFreeQ(void *mem);          /* $FA$_t_4d4880 */

int CDirDraw::DestroySurface(CDirDrawSurface *surf)
{
    if (surf == 0)
        return 0;
    dsurfDestroyQ(surf);
    dsurfFreeQ(surf);
    return 1;
}