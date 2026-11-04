// w43G chunk rva 0xd5f30 (100 B) = __flush_lk: MS CRT file flush (frameless, cdecl 1 param).
// FA: r=0(esi); f=param(edi); flags=[f+0xc] into eax; if ((cl&3)==2 && (eax&0x108)):
//     ptr([f+8]) loaded into eax first, cnt(ebx)=[f+0]-ptr; if cnt>0: push cnt, push ptr(eax),
//     reload eax=[f+0x10], push, call __write; if ret==cnt: reload [f+0xc] into eax, test al,0x80
//     -> [f+0xc] = flags2 & ~2 (and eax,fd); else: or [f+0xc],0x20; esi=-1.
// Tail: [f]=[f+8]; mov eax,esi; [f+4]=0 (elided c7 47 04); pops; ret.
// MANDATORY alias 0=$FA$_t_4d5f30 (FflushLk/FcloseLk/w38A_da510 map TOs).
extern long w43G_write(long fd, void *ptr, long cnt);

long w43G_flushlk_q(char *f)
{
    unsigned char flbyte;
    long r, flags, cnt, ptrv, f2;

    r = 0;
    flags = *(long *)(f + 0xc);
    flbyte = (unsigned char)flags;
    if ((flbyte & 3) == 2 && (flags & 0x108)) {
        ptrv = *(long *)(f + 8);
        cnt = *(long *)(f) - ptrv;
        if (cnt > 0) {
            if (w43G_write(*(long *)(f + 0x10), (void *)ptrv, cnt) == cnt) {
                f2 = *(long *)(f + 0xc);
                if (*(unsigned char *)(f + 0xd) & 0x80)
                    *(long *)(f + 0xc) = f2 & ~2;
            } else {
                *(long *)(f + 0xc) |= 0x20;
                r = -1;
            }
        }
    }
    *(long *)(f + 0) = *(long *)(f + 8);
    *(long *)(f + 4) = 0;
    return r;
}