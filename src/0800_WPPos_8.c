/* w40A_wppos_v2 — _WPPos@8 0x979e0 (160 B) v2: pointer q = &a1->x materialized
   (FA keeps it in ecx via lea ecx,[edx+6]), TE packed (fields at +11/+15/+19/+1d),
   16-bit table index (and eax,0xffff) */
#pragma pack(1)
typedef struct { char pad0[3]; unsigned char mode; char pad4[2]; int x; int y; int z; } A1;
#pragma pack()
typedef struct { int x; int y; int z; } V3;
#pragma pack(1)
typedef struct { char p[0x11]; int f11; int f15; int f19; unsigned short w1d; } TE;
#pragma pack()

extern int __stdcall T_Info(int, int, V3*, int, int, int);
extern int __stdcall WPObj(void*);
extern void __stdcall Rotate2(V3*, unsigned short);
extern void* _objPtrs[];

void __stdcall WPPos(A1* a1, V3* out)
{
    unsigned int* q = (unsigned int*)&a1->x;
    TE* e;
    out->x = q[0];
    out->y = q[1];
    out->z = q[2];
    if (a1->mode == 1)
        out->y += T_Info(0, 0, out, 0, 0, 0);
    else if (a1->mode >= 2 && a1->mode <= 3) {
        e = ((TE**)_objPtrs)[WPObj(a1) & 0xffffu];
        Rotate2(out, e->w1d);
        out->x += e->f11;
        out->y += e->f15;
        out->z += e->f19;
    }
}