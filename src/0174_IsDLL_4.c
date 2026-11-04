/* w32C isdll v3: v2 C re-spelled. FA (rva 0x1e450) inlines the 2-byte strcmp
 * (esi=h, eax=s2, dl=s2[i], ecx=nn, 3a 11 cmp dl,[ecx], sbb-pair sign tail,
 * 2-at-a-time stride with add eax,2/add ecx,2) — so spell the compare as a
 * strcmp() call for CL to inline the same shape, plus lfanew/pe split so the
 * sib [eax+esi*1] fold has a chance. */
extern int strcmp(const char *, const char *);
extern char brentDLLName;   /* -> ?setSoundAndMusic@@3JA+0x38 via map */
extern char __fastcall IsBrentDLLh(void *h);    /* -> _IsBrentDLL */

char __stdcall w32cIsDLLF3(void *h)
{
    unsigned long lfanew, pe;

    if (IsBrentDLLh(h)) {
        return 1;
    }
    if (*(unsigned short *)h != 0x5a4d) {
        return 0;
    }
    if (strcmp((char *)h + 0x4e, &brentDLLName) == 0) {
        return 0;
    }
    lfanew = *(unsigned long *)((char *)h + 0x3c);
    pe = *(unsigned long *)((char *)h + lfanew);
    if (pe == 0x4550) {
        return 1;
    }
    if (pe == 0x4c50) {
        return 1;
    }
    return 0;
}