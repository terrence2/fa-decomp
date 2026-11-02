/* ?CheckSndPurge@@YIXPAUT_HANDLE@@@Z @ rva 0x342d0 (64 B; 61 code + 3 pad).
   thiscall-style: param (T_HANDLE*) rides in ecx. do-while scans of
   MOD[0..15].atE and pendMOD[0..29].atE (dword reads at +0xe, stride
   0x54) against (int)h; then the word at h+0x10 gets |=8 unless bit2 set. */
#pragma pack(1)
typedef struct { char pad0[0xe]; int atE; char pad2[0x39]; char b4b; char pad3[8]; } w29c_modspec;
typedef struct { char pad0[0x10]; unsigned short w10; } w29c_thandle;
extern w29c_modspec w29c_MOD[];           /* _w29c_MOD -> ?MOD@@3PAUMODSPEC@@A */
extern w29c_modspec w29c_pMOD[];          /* _w29c_pMOD -> ?pendMOD@@3PAUMODSPEC@@A */

void __fastcall w29c_CSPq(w29c_thandle *h)
{
    int *p;

    if (h == 0)
        return;
    p = &w29c_MOD[0].atE;
    do {
        if (*p == (int)h)
            return;
        p += 21;
    } while (p < &w29c_MOD[16].atE);
    p = &w29c_pMOD[0].atE;
    do {
        if (*p == (int)h)
            return;
        p += 21;
    } while (p < &w29c_pMOD[30].atE);
    if ((h->w10 & 2) == 0)
        h->w10 |= 8;
}