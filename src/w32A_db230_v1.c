// 0xdb230 (35 B, unnamed) — v1: FILE getc macro shape: --cnt, js -> __filbuf
// call (returns its eax), else zero-read *ptr++ with store-first plan
typedef struct { char *p; long n; } w32a_fq;
extern long __cdecl w32a_filbuf(w32a_fq *f);   /* -> __filbuf (stub) */

long __cdecl w32a_getcsub(w32a_fq *f)
{
    if (--f->n < 0)
        return w32a_filbuf(f);
    return (long)(unsigned char)*f->p++;
}