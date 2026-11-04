/* FA 0x411ce0 _SpeedToXYZ@12 (112 B) */
struct F24P3 { long d0; long d1; long d2; };
extern struct F24P3 zeroF24Point3;      /* public 0x4e7710 */
extern void __stdcall Move3d(struct F24P3 *v, short x, short y, long n); /* _Move3d@16 */

void __stdcall SpeedToXYZ(const short *pos, long n, short *out)
{
    struct F24P3 v;

    v = zeroF24Point3;
    Move3d(&v, *(short *)pos, *(short *)((char *)pos + 2), n);
    *(short *)out = (short)(v.d0 >> 8);
    *(short *)((char *)out + 2) = (short)(v.d1 >> 8);
    *(short *)((char *)out + 4) = (short)(v.d2 >> 8);
}