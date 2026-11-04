/* w40A_ignore_v4 — @Ignore@4 0x63160 (160 B) v4: char return, fastcall ecx this,
   stdcall externs, shared fail tail with goto */
typedef unsigned char UC;
extern int __stdcall _Dist(void*, void*);
extern short __fastcall Abs1(short);
extern void __stdcall _AnglesOffNose(char*, void*, short*, short*);

char __fastcall Ignore(char* thisp)
{
    short a2, a1;
    int dist;
    dist = _Dist(thisp + 0x11, (void*)0x508749);
    if (*(UC*)(*(int*)(thisp + 0x5) + 0xe) & 0x20) {
        if (dist < 0x9c4000)
            goto fail;
        return 1;
    }
    if (dist < 0x26ac000) {
        _AnglesOffNose(thisp, (void*)0x508749, &a2, &a1);
        a2 = Abs1(a2);
        a1 = Abs1(a1);
        if (a1 > a2)
            a2 = a1;
        if (dist < 0x4e2000)
            goto fail;
        if (a2 < 0x4718)
            goto fail;
        return 1;
    }
    return 1;
fail:
    return 0;
}