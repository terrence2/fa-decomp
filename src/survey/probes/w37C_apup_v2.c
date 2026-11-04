/* _APUnassignPark@0 @ rva 0xb9830 (128 B) -- v2: ap = airports base,
 * end-chain = &airports[numAirports] re-evaluated in the loop; while
 * rotation gives entry pre-test + do-while bottom test.  pack(1) puts ids
 * at the odd offset +0x111; struct padded to the 0x134 FA element size. */
#pragma pack(1)
typedef struct {
    char p0[0xe0];
    short cnt;          /* +0xe0 */
    char p1[0x2f];
    short ids[1];       /* +0x111 */
    char p2[0x21];      /* +0x113..0x133 (element size 0x134) */
} AP7;
#pragma pack()

extern AP7 airports[];
extern short numAirports;
extern short curId;

void __stdcall w37c_apun(void)
{
    AP7 *ap;
    AP7 *end;
    long i;
    short *pid;

    ap = airports;
    end = &airports[numAirports];
    while (ap < end) {
        pid = &ap->ids[0];
        for (i = 0; i < ap->cnt; i++) {
            if (*pid == curId)
                *pid = 0;
            pid++;
        }
        ap++;
        end = &airports[numAirports];
    }
}