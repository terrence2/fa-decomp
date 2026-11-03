/* w32C pagetext v2: ?PageText@@YIPADJ@Z (rva 507984, 64 B incl 7B pad)
 * FA (rva 0x7c050): a1 [textNum]; mov edx,eax; shl eax,4; add eax,edx (eax=17*t);
 * mov edx,[fmtText+0x10][eax*4] (cnt); lea eax,[fmtText][eax*4] (bp); cmp edx,ecx;
 * jg body| xor eax,eax; ret. Body: lea ecx,[ecx*2] (page*=3); mov eax,[eax]
 * (p=*bp); mov eax,[eax+ecx*8+0x14]; cmp byte[eax],0x20; jae ret; mov cl,[eax+1];
 * inc eax; cmp cl,0x20; jb again; ret. No callees, no pushes. */
extern unsigned long textNum;   /* -> _textNum */
extern long fmtText[];          /* -> _fmtText */

char * __fastcall w32cPageTextF2(long page)
{
    long cnt;
    long *bp;
    char *p;
    unsigned char c;
    unsigned long i;

    i = textNum;
    i = (i << 4) + i;
    cnt = fmtText[i + 4];
    bp = &fmtText[i];
    if (cnt > page) {
        page = page + page + page;
        p = (char *)*bp;
        p = (char *)*(long *)(p + (page + page + 5) * 4);
        c = *(unsigned char *)p;
        if (c < 0x20) {
            do {
                c = *(unsigned char *)(p + 1);
                p = p + 1;
            } while (c < 0x20);
        }
        return p;
    }
    return (char *)0;
}