// 0x47060 _G_TileInit (51 B) — v3 (/Od + args (0x100,0x12c,0) matching FA's
// push stream; FA's trailing e9+0 join jmp is CL-dropped -> patched in)
extern char *__stdcall G_AllocBitmap27(long a, long b, long c);
extern char *bltBuffer27;  /* map _bltBuffer27=?bltBuffer@@3PAUT_HANDLE@@A */

void G_TileInit27(void)
{
    if (bltBuffer27 == 0)
        bltBuffer27 = G_AllocBitmap27(0x100, 0x12c, 0);
}
