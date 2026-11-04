/* w40A_dc580_v1 — unnamed 0xdc580 (75 B): stream buffer allocator; incs
   __cflush, mallocs 0x1000 or falls back to an inline 2-elem buffer at s+0x14 */
typedef struct { unsigned p0; unsigned p4; unsigned buf; unsigned flg; char pad[8]; unsigned sz; } ST;

extern unsigned __cflush;
extern unsigned* __cdecl malloc(unsigned);

void sub_dc580(ST* s)
{
    __cflush++;
    s->buf = (unsigned)malloc(0x1000);
    if (s->buf) {
        s->flg |= 8;
        s->sz = 0x1000;
    } else {
        s->flg |= 4;
        s->buf = (unsigned)((char*)s + 0x14);
        s->sz = 2;
    }
    s->p0 = s->buf;
    s->p4 = 0;
}