/* v3: src++ as a separate trailing statement (FA schedules the two dst
 * incs together before the src inc: 40 40 41). */
extern unsigned char w36g_hex[];   /* ?spx_proto@@3UNET_PROTOCOL@@A+0x70 */

char *hbtoa(unsigned char *src, short len, char *dst)
{
    short n = (short)len;
    if (n > 0) {
        do {
            n--;
            *dst++ = w36g_hex[*src >> 4];
            *dst++ = w36g_hex[*src & 0xf];
            src++;
        } while (n != 0);
    }
    *dst = 0;
    return dst;
}