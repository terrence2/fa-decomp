/* @MSGMultiGet@4 v2: plain C fastcall — v2 field-index fix: type at p+4,
 * free flag at p+6, restore writes p+6. FA-side calls: PushCurObj(q) after
 * *p = *q++ (FA's movs advances esi; q is FA's esi value). Checks in FA's
 * end-block order so the restore/out blocks land at the tail. */
extern char lastWeaponButton;
extern void *_objPtrs[];
extern unsigned short currentT;
void __stdcall PushCurObj(unsigned long);
void __stdcall ImmediateService(void);
void __stdcall PopCurObj(void);

typedef struct MQ { char b[213]; } MQ;

void __fastcall MSGMultiGet(MQ *q)
{
    MQ *p;
    unsigned short t, n, cur;
    void *cls;
    unsigned long f;
    unsigned short w;
    p = (MQ *)((char *)&lastWeaponButton + 0xf0);
    do {
        if (*(unsigned short *)((char *)p + 6) == (unsigned short)0xffff)
            goto found;
        p++;
    } while ((char *)p < (char *)&lastWeaponButton + 0x64c8);
    return;
found:
    *(MQ *)p = *q++;
    t = *(unsigned short *)((char *)p + 4);
    if (t >= (unsigned short)0x8003 && t <= (unsigned short)0x800b)
        goto out;
    cls = _objPtrs[t];
    f = *(long *)((char *)cls + 1);
    if (!(f & 1))
        goto restore;
    if (!(f & 2))
        goto out;
    n = *(unsigned short *)((char *)cls + 0x68);
    cur = currentT;
    cur++;
    if (n <= cur)
        goto out;
    PushCurObj((unsigned long)q);
    ImmediateService();
    PopCurObj();
    return;
restore:
    *(unsigned short *)((char *)p + 6) = (unsigned short)0xffff;
out:
    return;
}