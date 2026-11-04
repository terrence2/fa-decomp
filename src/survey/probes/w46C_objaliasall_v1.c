// Wave 46 batch C entry 7: _OBJAliasAll@12 @ rva 587728 (0x8f7d0), 176 B.
// Walks all objects (objPtrs[] up to _nextObjId): for in-use types 2/4, re-alias
// the preferred pointer via _OBJAliasPreferred@16 and walk the +0xe8 waypoint
// list (0x44-stride records, bit1 terminator) via _OBJAliasWaypoint@16.
// stdcall 3 args (byte, word, word), sub esp,4 with word local idx at +2.
// Tail pad: 8d 49 00 + 8d a4 24 00 00 00 00 (10 B).
#pragma pack(1)
typedef struct { unsigned char type; unsigned long flag; char q2[0xe3];
                 void *sub; char q3[4]; void *pref; } W46AOBJ;
typedef struct { unsigned char f0; char q4[0x43]; } W46AREC;

extern unsigned short nextObjId;
extern void *objPtrs[];
extern void *__stdcall OBJAliasPreferred(void *p, char a, short b, short c);
extern void __stdcall OBJAliasWaypoint(void *r, char a, short b, short c);

void __stdcall OBJAliasAll(char a0, short a1, short a2)
{
    unsigned short w;
    W46AOBJ *obj;
    W46AREC *sub;
    void *fp;

    w = 1;
    if (nextObjId > 1) {
        do {
            obj = ((W46AOBJ **)objPtrs)[w];
            if (obj->flag & 1) {
                if (obj->type == 2 || obj->type == 4) {
                    fp = obj->pref;
                    if (fp) {
                        obj->pref = OBJAliasPreferred(fp, a0, a1, a2);
                    }
                    sub = (W46AREC *)obj->sub;
                    if (sub && !(sub->f0 & 2)) {
                        do {
                            OBJAliasWaypoint(sub, a0, a1, a2);
                            sub = (W46AREC *)((char *)sub + 0x44);
                        } while (!(sub->f0 & 2));
                    }
                }
            }
            w++;
        } while (w < nextObjId);
    }
}