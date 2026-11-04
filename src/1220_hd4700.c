/* wave-40F probe v2: 0xd4700 (41 B) 8-arg cdecl forwarding thunk.
   FA callee args (push order 0,s,f10,f8,0,u3,fc,u1) => callee(u1, s->fc, u3, 0, s->f8, s->f10, s, 0). */
typedef struct S47 {
    char p0[8];   /* +0 */
    long f8;      /* +8 */
    long fc;      /* +0xc */
    long f10;     /* +0x10 */
} S47;

void w40f_fwd(long, long, long, long, long, long, long, long);  /* $FA$_t_4d85e0 */

void __cdecl w40f_d4700(long u1, S47 *s, long u3, long u4)
{
    w40f_fwd(u1, s->fc, u3, 0, s->f8, s->f10, s, 0);
}