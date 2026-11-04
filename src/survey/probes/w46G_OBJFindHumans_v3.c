/* _OBJFindHumans@0 @ 0x8f4a0 (160 B): scan obj slots for players.  v2 —
 * FA statement order (stores interleaved with pushes, pw base hoisted via
 * mov ecx,&obj feeding the [ecx+8]/[ecx+0xc] dword stores, slot word-store
 * via the pw pointer).
 * void __stdcall OBJFindHumans(void)
 *   playerId(0x51c2cc W)=0; obj[0](0x4e7610)=0; playerWMId(0x51c2c4 W)=0;
 *   obj[1](0x4e7614)=0; push esi; pw=(ushort*)obj (b9 mov ecx,&obj);
 *   push edi; push ebp; i=1 (esi); obj[2]=[ecx+8]=0;
 *   cmp word nextObjId(0x54ad88),si; obj[3]=[ecx+0xc]=0; jbe exit;
 *   m = i (mov edi,esi);
 *   loop: p = objPtrs[i & 0xffff]; [and eax,0xffff; mov ebp,[eax*4]];
 *     if (*(long*)((char*)p+1) & m == 0) continue;  [test [ebp+1],edi; je]
 *     b = p[0x10]; if (!(b & 0x80)) continue;
 *     and ebx,0x7f;
 *     if (thisComputer(0x4e7608) == pid) { playerId = i;
 *         playerWMId = WNGPlayerWM(); [66 a3 ax] }
 *     pw[pid] = i;  [66 89 34 5d — SIB*2]
 *     hs = p[9] & 0x80; humanChoseSide[pid](0x51c2d8) = hs;
 *     i++; while (i < nextObjId) -- body re-entry skips m=i
 * exit: pop ebp/edi/esi/ebx; ret   (5d 5f 5e 5b c3 @ tail, 8bff+lea pads)
 */
extern unsigned short playerId;               /* 0x51c2cc */
extern unsigned short playerWMId;             /* 0x51c2c4 */
extern unsigned long objControlledBy[8];      /* 0x4e7610 */
extern unsigned long humanChoseSide[16];      /* 0x51c2d8 */
extern unsigned long objPtrs[4096];           /* 0x54ad98 */
extern unsigned short nextObjId;              /* 0x54ad88 */
extern unsigned long thisComputer;            /* 0x4e7608 */
extern unsigned long __stdcall WNGPlayerWM(void);

void __stdcall OBJFindHumans(void)
{
    unsigned short i;
    unsigned long m;
    unsigned long *p;
    unsigned char b;
    unsigned long hs;
    unsigned short *pw;

    playerId = 0;
    objControlledBy[0] = 0;
    playerWMId = 0;
    objControlledBy[1] = 0;
    pw = (unsigned short *)objControlledBy;
    i = 1;
    *(unsigned long *)((unsigned char *)pw + 8) = 0;
    if (nextObjId > i) {
        *(unsigned long *)((unsigned char *)pw + 0xc) = 0;
        m = i;
        while (nextObjId > i) {
            p = (unsigned long *)objPtrs[i & 0xFFFF];
            if (*(long *)((char *)p + 1) & m) {
                b = ((unsigned char *)p)[0x10];
                if (b & 0x80) {
                    long pid = b & 0x7f;
                    if (thisComputer == (unsigned long)pid) {
                        playerId = i;
                        playerWMId = (unsigned short)WNGPlayerWM();
                    }
                    pw[pid] = i;
                    hs = ((unsigned char *)p)[9] & 0x80;
                    humanChoseSide[pid] = hs;
                }
            }
            i++;
        }
    }
}