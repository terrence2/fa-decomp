/* w46D Angles rva 71632 (0x4117d0) v2 */
struct W46AB { short a, b; };
struct W46CD { short c, d; };
struct W46PW { struct W46AB ab; struct W46CD cd; };
extern unsigned long __stdcall GetWordPointDelta_q(unsigned long, unsigned long, struct W46PW*);
extern int __fastcall ArcTan_q(int, int);
extern int __fastcall Abs_q(struct W46CD);
extern int __fastcall Abs2_q(struct W46AB);
extern int __fastcall Sqrt_q(int);

void __stdcall w46d_angles_q(unsigned long p1, unsigned long p2,
                             struct W46PW* o1, struct W46PW* o2)
{
    volatile struct W46PW w;
    short t;
    int cc, aa;
    GetWordPointDelta_q(p1, p2, &w);
    if (o1)
        o1->ab.a = (short)ArcTan_q(w.ab.a, w.cd.c);
    if (o2) {
        if (w.ab.a == 0)
            t = (short)Abs_q(w.cd);
        else if (w.cd.c == 0)
            t = (short)Abs2_q(w.ab);
        else {
            cc = w.cd.c * w.cd.c;
            aa = w.ab.a * w.ab.a;
            t = (short)Sqrt_q(cc + aa);
        }
        w.ab.a = t;
        t = (short)ArcTan_q(w.ab.b, w.ab.a);
        o2->ab.a = t;
        if (t > 0x3ffc)
            o2->ab.a = 0x3ffc;
        if (o2->ab.a < -0x3ffc)
            o2->ab.a = 0xc004;
    }
}