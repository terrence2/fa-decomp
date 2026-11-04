// $FA$_t_4d6fc0 (65 B) — buffered putc helper referenced by converted
// w41F_loop1_v3 (map _w41F_loopG=$FA$_t_4d6fc0); converting this chunk
// REQUIRES retro-alias "0=$FA$_t_4d6fc0" on this entry.
// FA: edx=[esp+8](b)/eax=[b+4]/dec/js flush/[b+4]=eax/eax=[b](ptr)/cl=[esp+4](c)/
//   [eax]=cl/ecx=[b]/xor eax/8a 01/inc ecx/[b]=ecx/jmp common/
//   flush: ecx=[esp+4]/push edx/push ecx/call $FA$_t_4d64c0/add esp,8/
//   common: cmp eax,-1/eax=[esp+0xc](cnt)/jne +7/[eax]=-1/ret/inc [eax]/ret
extern long __cdecl w42D_bpflush(long c, void *b);   /* $FA$_t_4d64c0 */

long w42D_bufPut(long c, void *b, long *cnt)
{
    long d;
    long r;

    d = *(long *)((char *)b + 4);
    if (--d < 0) {
        r = w42D_bpflush(c, b);
    } else {
        *(long *)((char *)b + 4) = d;
        *(char *)(*(char **)b) = (char)c;
        r = *(unsigned char *)(*(char **)b);
        *(char **)b += 1;
    }
    if (r == -1)
        *cnt = -1;
    else
        (*cnt)++;
    return (long)cnt;
}