/* nameless chunk @ rva 0x87050 (32 B) — cdecl void(16-bit POINT-ish *):
 * pt->x -= curDialog->[8] (word); pt->y -= curDialog->[0xa] (word).
 * FA reloads ?curDialog@@3PAUDIALOG@@A twice (a1 + 8b15). */
struct w34d_pt { unsigned short x, y; };
struct w34d_dlg { char pad[8]; unsigned short x, y; };
extern struct w34d_dlg *w34d_cdl;  /* =?curDialog@@3PAUDIALOG@@A */

void __cdecl w34d_87050(struct w34d_pt *pt)
{
    pt->x -= w34d_cdl->x;
    pt->y -= w34d_cdl->y;
}