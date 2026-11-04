/* w36F 0xbe2b0 (64B, tail 8da42400000000 x2) v1 — objPtrs validity check
 * FA: test cx,cx; je ret0; cmp cx,0xffff; je ret0; and ecx,0xffff;
 * mov eax,[ecx*4+objPtrs]; mov cl,[eax+0x10]; test cl,0x80; je cont;
 * ret0: xor al,al; ret; cont: mov eax,[eax+5]; test byte[eax+0xe],0xc0;
 * sete al; ret
 */
extern char *objPtrs[4];   /* bare public _objPtrs @ 0x54ad98 */

char __fastcall w36f_objchk(unsigned short i)
{
    char *p;
    unsigned char t;
    char *q;
    if (i == 0 || i == 0xffff) {
        return 0;
    }
    p = objPtrs[i];
    t = p[0x10];
    if (t & 0x80) {
        return 0;
    }
    q = *(char **)(p + 5);
    return !(q[0xe] & 0xc0);
}