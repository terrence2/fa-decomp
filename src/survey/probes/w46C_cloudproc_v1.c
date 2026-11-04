// Wave 46 batch C entry 8: ?T_CloudProc@@YAXJ@Z @ rva 678416 (0xa5a10), 144 B.
// Global ambient cloud proc: if *(long*)_cloudAlt, walk the 0x1a-stride record
// list at _cloudAlt+0x14 (terminator field0==0), storing (*_cloudAlt)<<8 into
// each record+0x10; then dispatch by *(short*)(_v+0x8c): <2 -> stub fn2 (11
// args) else stub fn1 (10 args), both __stdcall (ret 0x2c / ret 0x28).
// Callees are unnamed stubs -> maps to $FA$_t_4a4fa0 / $FA$_t_4a4f00.
// 2-B tail pad 8b ff (code 0x8e).
extern volatile unsigned long w46c_cldv;    /* _cloudAlt                    */
extern volatile unsigned long w46c_recs0;   /* _cloudAlt+0x14 (record0 f0)  */
extern unsigned char w46c_cldp[];           /* _cloudAlt+0x14 (pushed addr) */
extern short w46c_md;                       /* _v+0x8c                      */

extern void __stdcall w46c_cfn1(long, unsigned char *, long, long, long, long,
                                 long, long, long, long);
extern void __stdcall w46c_cfn2(long, unsigned char *, long, long, long, long,
                                long, long, long, long, long);

void __cdecl w46c_tcq(long p)
{
    unsigned char *r;
    unsigned long v;

    if (w46c_cldv == 0)
        return;
    r = (unsigned char *)&w46c_recs0;
    if (w46c_recs0 != 0) {
        do {
            v = w46c_cldv;
            r += 0x1a;
            *(volatile unsigned long *)(r - 0xa) = v << 8;
        } while (*(volatile unsigned long *)r != 0);
    }
    if (w46c_md >= 2) {
        w46c_cfn1(-1, (unsigned char *)w46c_cldp, 3, 0x7fffffff, 0,
                  0x7fffffff, 0, 0x7fffffff, 0x2000000, 2);
        return;
    }
    w46c_cfn2(-1, (unsigned char *)w46c_cldp, 3, 0x7fffffff, 0,
              0x7fffffff, 0, 0x7fffffff, 0, 0, 0x2000000);
}