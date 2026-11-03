/* rva 0x110c0 (69824), 32 B - 16-bit running-min into _dam+0x75,
   fastcall arg in cx. */
extern unsigned short w33g_ct;    /* -> _currentTime */
extern unsigned short w33g_dmin;  /* -> _dam+0x75 */

unsigned short __fastcall w33g_smin(unsigned short t)
{
    unsigned short r;
    r = w33g_ct + t;
    if (r < w33g_dmin)
        w33g_dmin = r;
    return r;
}
