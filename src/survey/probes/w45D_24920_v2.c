/* probe w45D_24920 (FA 0x424920, 128B): wing/object flag updater fastcall(ecx,edx) */
extern void *w45D_ops[];               /* _objPtrs */
unsigned long __stdcall WPTarget(unsigned char *);

void __fastcall w45D_24920(unsigned char *src, unsigned char *wp)
{
    unsigned long id, t;
    unsigned char *o;
    unsigned char x;

    id = *(unsigned long *)(wp + 0x21);
    if (id == 0)
        goto bad;
    t = WPTarget(wp);
    if ((t & 0xffff) == 0)
        goto bad;
    o = ((unsigned char **)w45D_ops)[t & 0xffff];
    if (o == 0)
        goto bad;
    if ((*(unsigned long *)(o + 1) & 1) == 0)
        goto bad;
    x = src[9] ^ o[9];
    id = *(unsigned long *)(wp + 0x21);
    if (x & 0x80) {
        id &= 0xbfffffff;
        *(unsigned long *)(wp + 0x21) = id;
    } else {
        id |= 0x40000000;
        x = wp[1] & 0xe3;
        *(unsigned long *)(wp + 0x21) = id;
        wp[1] = x;
    }
    goto check;
bad:
    *(unsigned long *)(wp + 0x21) = 0;
    wp[1] &= 0xe3;
check:
    if (wp[1] == 0)
        wp[1] = 1;
}