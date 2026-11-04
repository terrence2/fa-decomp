/* rva 0x26cd5 (88 B) - remove object (fastcall id in cx, flag in dl) */
extern char curThingQ[];
extern long specialsQ[64];
extern unsigned char __fastcall w43aCheck2(unsigned short, long);
extern long __fastcall w43aGetCurObj(unsigned short);
extern void w43aQ45db50(void);
extern void w43aQ5e880(void);
extern void w43aPutCurObj2(void);
extern void __fastcall w43aAPDel(unsigned short);
extern void w43aQ22368(void);
extern void __fastcall w43aQ3de0(long);

void __fastcall w43A_26cd5(unsigned short id, unsigned char fl)
{
    if (w43aCheck2(id, 1)) {
        w43aGetCurObj(id);
        *(volatile unsigned char *)(curThingQ + 1) &= (unsigned char)0xfe;
        if (fl) {
            w43aQ45db50();
            w43aQ5e880();
        }
        w43aPutCurObj2();
        w43aAPDel(id);
        w43aQ22368();
        w43aQ3de0(0);
        specialsQ[50] = 0;
    }
}
