/* w40A_tlistfind_v2 — unnamed 0x23ad0 (64 B) v2: _tlistSize is a byte COUNT,
   end = (W*)((char*)_tlist + _tlistSize) via lea esi,[esi*1+_tlist] */
typedef unsigned short W;
extern char _tlist[];
extern unsigned _tlistSize;

W* __fastcall tlistFind(W k1, W k2)
{
    W* p;
    W* end;
    k1 &= 0xfffcu;
    k2 &= 0xfffcu;
    end = (W*)((char*)_tlist + _tlistSize);
    p = (W*)_tlist;
    if (end <= p)
        return 0;
    for (; p < end; p += 4) {
        if (p[0] == k1 && p[1] == k2)
            return p;
    }
    return 0;
}