// @CallDamageProc@4 @ rva 0x63080 = 405632, 112 B.
extern unsigned long __stdcall RMAccessQ(void *, unsigned long); /* map _RMAccessQ@8=_RMAccess@8+0x5 */
extern unsigned long __stdcall grpDmgQQ(void *, unsigned long); /* map _grpDmgQQ@8=$FA$_t_4630f0 */
extern unsigned long objPtrs[];
extern unsigned long __stdcall RemoveCurObj(void);
extern unsigned long cdD1;   /* _curThing+0x1 (dword; FA tests bit 0 via a1+a8) */
extern unsigned short cdW0e; /* _curThing+0xe (word ==0 via 66 83 3d) */
extern unsigned long cdT9;   /* _curThingType+0x9 (dword; FA tests 0x400 via ah) */

typedef unsigned long (__cdecl *CDP_VQ)(unsigned long);

void __fastcall CallDamageProcQ(char *o)
{
    unsigned long r;
    unsigned short w;
    w = *(unsigned short *)(o + 1);
    if (w != 0)
        r = grpDmgQQ((void *)objPtrs[w], 4);
    else
        r = (*(CDP_VQ)(*(unsigned long *)((char *)RMAccessQ(o + 3, 0x8000) + 0x7d)))(4);
    if (r)
        ((void (__cdecl *)(void *))r)(o);
    if ((cdD1 & 1) && (cdW0e == 0) && (cdT9 & 0x400))
        RemoveCurObj();
}