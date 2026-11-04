/*
 * w44D_23a13_v1.c — unnamed @ 0x423a13 (93 B, fpo/esp, locals=1)
 * Fastcall(word id in cx, int x in edx).  Guards curScreen==0x0c,
 * numComputers!=1, x!=0.  0x421cd0 takes (x, &slot, 0): slot aliases
 * FA's single local dword (store + out-buffer).  Word var rides in si.
 */
extern unsigned short curScreen;
extern int numComputers;
extern int __fastcall w44dSub21cd0(int a, int *b, int c);
extern unsigned short __fastcall w44dSub24ae3(int a);
extern void __fastcall MPSetWaypoints(unsigned short a, void *b);

void __fastcall FA_23a13(unsigned short id, int x)
{
    unsigned short w = id;
    int slot = x;
    if (curScreen == 0x0c && numComputers != 1 && x != 0) {
        w44dSub21cd0(slot, &slot, 0);
        if (w == 0)
            w = w44dSub24ae3(slot);
        MPSetWaypoints(w, (void *)slot);
    }
}