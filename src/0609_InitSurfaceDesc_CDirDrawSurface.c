// ?InitSurfaceDesc@CDirDrawSurface@@SAXPAU_DDSURFACEDESC@@@Z @ rva 0x778b0
// (32 B) — FA asm:
//   mov edx,[esp+4] / push edi / test edx,edx / je / mov edi,edx / xor eax,eax /
//   mov ecx,0x1b / rep stosd (f3 ab) / mov [edx],0x6c / pop edi / ret
// if (p) { memset(p,0,0x6c); *(int*)p = 0x6c; } — the <string.h> include
// makes CL 4.2 inline memset as rep stosd (wave-6 rule), 0x6c/4 = 0x1b dwords,
// and the dwSize store takes the ORIGINAL edx base (not edi). Plain C exact
// (probe b18c_InitSurfaceDesc, zero diffs).
#include <string.h>

void InitSurfaceDesc(char *p)
{
    if (p) {
        memset(p, 0, 0x6c);
        *(int *)p = 0x6c;
    }
}
