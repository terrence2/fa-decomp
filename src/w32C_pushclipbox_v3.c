/* w32C pushclipbox v3: v2 C + slot2 alias trick. CL v2 folded the slot
 * pointer away (kept moffs-sib per store with an imm each); FA materializes
 * lea ecx once (site) then reg-stores [ecx+2/4/6]. A second distinct extern
 * (same VA via map) for the e-pointer defeats the CSE so CL emits the lea.
 * FA (rva 0x95740, 64 B): push ebx; a1 [g2s]; 40 inc; 8b 15 [clipLeft] (edx);
 * a3 [g2s]; 66 89 14 c5 [slot+eax*8],dx; 8d 0c c5 lea ecx; 8b 1d [clipTop]
 * (ebx); 66 89 59 02; 5b pop ebx; a1 [clipWidth]; 66 89 41 04;
 * 8b 15 [clipHeight]; 66 89 51 06; c3. */
extern long g2s;        /* _g2s = _globalSecondarySurface+0x4 */
extern long clipLeft;   /* _clipLeft */
extern long clipTop;    /* _clipTop */
extern long clipWidth;  /* _clipWidth */
extern long clipHeight; /* _clipHeight */
extern long slotBase[]; /* _slotBase = _tempYLR+0x4e18 (index-form store) */
extern long slot2[];    /* same VA, distinct symbol to break CSE (lea) */

void __fastcall w32cPushClipF3(void)
{
    long i;
    short c;
    short *e;

    i = g2s;
    i = i + 1;
    c = clipLeft;
    g2s = i;
    *(short *)(slotBase + i + i) = c;
    e = (short *)&slot2[i + i];
    c = clipTop;
    e[1] = c;
    c = clipWidth;
    e[2] = c;
    c = clipHeight;
    e[3] = c;
}