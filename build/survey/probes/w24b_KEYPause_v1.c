/* probe v1 */
extern unsigned short kbCountX;   /* ?kbCount@@3GA */
extern unsigned short kbHeadX;    /* ?kbHeadPtr@@3GA */
extern unsigned short kbTailX;    /* ?kbTailPtr@@3GA */
extern unsigned short keyarrX[];  /* &_keyarray */
extern unsigned char qualX;       /* _qualStatus */
extern unsigned char kflagX;      /* _keyFlags */

void *memset(void *d, int v, unsigned int n);

void __cdecl KEYPause_q(void)
{
    unsigned short z0;
    z0 = 0;
    kbCountX = z0;
    kbTailX = z0;
    kbHeadX = z0;
    memset(keyarrX, 0, 0x100);
    qualX = (unsigned char)z0;
    kflagX = (unsigned char)z0;
}
