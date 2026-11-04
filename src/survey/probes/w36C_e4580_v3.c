/* w36C 0xe4580 _iswctype v3: return operand order = mask & tmpX (FA tail
 * reads mask's slot first: mov ax,[esp+0xc]; and ax,[esp+2]), no casts on
 * the return (int promotion should give movzx, not and eax,0xffff). */
#define tmpX (*(unsigned short *)((char *)&buf + 2))

extern unsigned long ctypeLkX;  /* _ctypeLkX=__ctype+0x388 */
extern void *_pwctype;          /* identity __pwctype */

extern unsigned long __cdecl wLkTblX(int a1, unsigned short *pc, int a3,
                                     unsigned short *ptmp, int a5, int a6);
/* _wLkTblX=$FA$_t_4dc7f0 (still-stub t000e6; 0x4dc4f0..0x4dcad3) */

int iswctype_36(unsigned short c, unsigned short mask)
{
    unsigned long buf;

    if (c == 0xffff)
        return 0;
    if (c < 0x100)
        tmpX = ((unsigned short *)_pwctype)[(unsigned long)c];
    else {
        if (ctypeLkX == 0)
            return 0;
        if (wLkTblX(1, &c, 1, (unsigned short *)((char *)&buf + 2), 0, 0) == 0)
            return 0;
    }
    return mask & tmpX;
}