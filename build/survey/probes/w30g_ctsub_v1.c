// unnamed chunk @ rva 0x6eaf0 (32 B) — fastcall short param in cx:
// if (x == 0x7fff || x == 0) return x; return x - _currentT (16-bit sub
// moffs). False arm first, return-x block tailed after it.
extern short w30gCurT;    // = _currentT+0 (16-bit read)

short __fastcall w30g_ctsub(short x)
{
    if (x == 0x7fff || x == 0)
        return x;
    return x - w30gCurT;
}