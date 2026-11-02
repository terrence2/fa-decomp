// ?dlg_list_get_new_selection@@YADPAXPAUNET_ADDRESS@@PAD@Z @ rva 0x63a40 — C v2 (a19 field at +0x19)
typedef struct { char pad0[4]; long a4; char rest[0x11]; char a19; } SELS;
extern char __cdecl dlgselX(SELS *s, void *a2, char *a3);

char __cdecl dlg_list_get_new_selectionq(SELS *s, void *a2, char *a3, char *str)
{
    if (s->a4 && s->a19)
        return dlgselX(s, a2, a3);
    return 0;
}
