// _HARDGunsOnlyAll@0 @ rva 0x52a60 (80 B) — probe v1.
extern char curThingQ[];   /* _curThing */
extern unsigned short nextObjId;  /* _nextObjId */
extern void __fastcall GetCurObj_q(unsigned short idx); /* @GetCurObj@4 */
extern void hardgunsQ(void); /* _HARDGunsOnly@0 */
extern void __fastcall PutCurObj_q(void); /* @PutCurObj@0 */

void __stdcall HARDGunsOnlyAll_q(void)
{
    unsigned short i = 1;
    unsigned short m, t;
    if (nextObjId > i) {
        m = i;
        t = 4;
        do {
            GetCurObj_q(i);
            if (*(unsigned long *)&curThingQ[1] & m)
                if (t == *(char *)&curThingQ[0])
                    hardgunsQ();
            i++;
            PutCurObj_q();
        } while (i < nextObjId);
    }
}
