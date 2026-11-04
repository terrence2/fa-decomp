/* ?CheckSndLink@@YAXPAUMODSPEC@@@Z @ rva 0x35610 (96 B): void
 * CheckSndLink(MODSPEC* mod) — idx = movsx mod->f2e; -1 early out;
 * idx<16: p = &MODTbl[idx] (MODSPEC[32] at 0x53c028); else struct-copy
 * tmpl[idx] (MODSPEC[16] at _specials+0xb30) into *mod then
 * tmpl[idx].ref = 0; shared tail: if (p->ref && p->ref->f8)
 * { p->f4b = 1; p->f1e = 0; }. sizeof(MODSPEC) = 0x54. */
#pragma pack(push, 1)
struct MSREF { unsigned char pad8[8]; unsigned long f8; };
struct W36G_MODSPEC {
    unsigned char pad0e[0x0e];
    struct MSREF  *ref;
    unsigned char pad1e[0x1e - 0x12];
    unsigned long f1e;
    unsigned char pad22[0x2e - 0x22];
    short f2e;
    unsigned char pad30[0x4b - 0x30];
    unsigned char f4b;
    unsigned char pad4c[0x54 - 0x4c];
};
#pragma pack(pop)
extern struct W36G_MODSPEC w36g_mods[];   /* ?MOD@@3PAUMODSPEC@@A */
extern struct W36G_MODSPEC w36g_tmpl[];   /* _specials+0xb30 */
extern void *memcpy(void *, const void *, unsigned);

void CheckSndLink(struct W36G_MODSPEC *mod)
{
    int idx;
    struct W36G_MODSPEC *p;
    idx = mod->f2e;
    if (idx == -1)
        return;
    p = mod;
    if (idx < 16)
        p = &w36g_mods[idx];
    else {
        memcpy(mod, &w36g_tmpl[idx], sizeof(struct W36G_MODSPEC));
        w36g_tmpl[idx].ref = 0;
    }
    if (p->ref != 0 && p->ref->f8 != 0) {
        p->f4b = 1;
        p->f1e = 0;
    }
}
