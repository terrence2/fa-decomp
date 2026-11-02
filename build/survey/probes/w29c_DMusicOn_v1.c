/* ?DMusicOn@@YIXPADF@Z @ rva 0x324d0 (64 B; 51 code + 13 pad).
   thiscall-style YI chunk: push esi / a0 [flag@4e75f0] / mov esi,ecx /
   test / je end / 66 83 3d [musicId],-1 / je skip / call DMusicOff /
   66 a1 [volDMusic] / push 0 / push 0x29 / push eax / push esi /
   call SingleSound / 66 a3 [musicId],ax / pop esi / ret.
   thiscall -> __fastcall probe shim (one reg arg, no stack args so the
   plain FA ret falls out); this rides in untouched ecx until the
   DMusicOff call, p (the same ecx) is spilled to esi for both uses. */
extern char w29c_dmFl;                    /* _w29c_dmFl -> $FA$_d_4e7000+0x5f0 */
extern short w29c_mId;                    /* _w29c_mId -> ?musicId@@3FA */
extern short w29c_volD;                   /* _w29c_volD -> ?volDMusic@@3FA */
extern void __cdecl w29c_DMOX(void);      /* ?DMusicOff@@YIXXZ */
extern short __stdcall w29c_SSXq(char *file, short v2, short v3, short v4);  /* ?SingleSound@@YGFPADFEF@Z */

void __fastcall w29c_DMoq(char *p)
{
    if (w29c_dmFl) {
        if (w29c_mId != -1)
            w29c_DMOX();
        w29c_mId = w29c_SSXq(p, w29c_volD, 0x29, 0);
    }
}