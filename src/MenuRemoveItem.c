// ?MenuRemoveItem@@YAXJ@Z @ rva 0xbf20 (48 B) — unlink menu item idx from the
// shared menu chain (cdecl — FA exits are plain ret, caller cleans).
// FA: push esi; xor ecx; esi=[firstMenu] (8b 35); cmp esi,ecx (3b f1 — the
// live zero pos register, not test); while (esi) re-reading [esp+8] (idx)
// EVERY iteration: if (pos-idx == -1) unlink esi->[0]; walk esi=[esi], pos++.
// pos=0 BEFORE the firstMenu load so CL xors ecx first and 3b f1-compares.
typedef struct MENU MENU;
struct MENU { MENU *next; };
extern MENU *firstMenu;

void __cdecl MenuRemoveItem(long idx)
{
    MENU *p;
    long pos = 0;

    p = firstMenu;
    if (p == 0)
        return;
    while (p) {
        if (pos - idx == -1) {
            if (p->next)
                p->next = p->next->next;
            return;
        }
        p = p->next;
        pos++;
    }
}
