// Wave 46 batch C entry 6: ?HARDBestSeekers@12 @ rva 336816 (0x523b0), 208 B.
// __fastcall(ecx=arg0 byte, edx=dest array, stack arg2 byte): zeroes the 5x12-B
// dest records (rep stosd), then ring-scans items via _HARDFindStore@12
// (cursor local init 0x7fffffff) + _HARDPtrs@12, filters type/p0/team-flag,
// and keeps the minimum best-value per hardpoint slot.
// FPO esp, locals=8, params=0xc, cbProlog: sub8, push ebx/esi/edi, mov esi,edx,
// push ebp, mov bl,cl, mov edi,esi. Codes: ret 4 exit; 7 B pad 8da424000000.
typedef struct { long ptr; short val; short idx; short x; short y; } W46CD;

extern long __stdcall HARDFindStore(long *cursor, long a, long b);
extern long __stdcall HARDPtrs(long idx, long **rec, long z);

void __fastcall HARDBestSeekers(char p0, W46CD *dest, char p2)
{
    long *rec;
    long cursor;
    long idx, item, t, hv, hb;
    W46CD *d;

    memset(dest, 0, 0x3c);
    cursor = 0x7fffffff;
    for (;;) {
        idx = HARDFindStore(&cursor, 0xA, 7);
        if (idx == -1)
            break;
        item = HARDPtrs(idx, &rec, 0);
        if (!item)
            continue;
        t = *(char *)item;
        if (t == 7) {
            if (!p2)
                continue;
            item += 0xac;
        }
        if (*(short *)((char *)rec + 4) <= 0)
            continue;
        if (p0 != (char)-1 && *(char *)(item + 8) != p0)
            continue;
        hv = (short)((*(long *)((char *)item + 0x17)) >> 16);
        hb = (unsigned long)(unsigned char)*(long *)(item + 8);
        d = &dest[hb];
        if (d->ptr != 0) {
            if ((long)(unsigned short)d->val <= (long)hv)
                continue;
        }
        d->ptr = item;
        d->val = (short)hv;
        d->idx = (short)idx;
        d->x = *(short *)((char *)rec + 6);
        d->y = *(short *)((char *)rec + 8);
    }
}