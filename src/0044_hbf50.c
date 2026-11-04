/* rva 48976 (0xbf50) 32 B FPO gap chunk
 * push ebx (dead) + mov ecx,ds:?firstMenu@@3PAUMENU@@A;
 * while (p->next->next) p = p->next; p->next = 0 */
typedef struct W30H_MENU { struct W30H_MENU *next; } W30H_MENU;
extern W30H_MENU *w30h_firstMenu;

void w30h_menuTrim(void)
{
    W30H_MENU *p = w30h_firstMenu;

    while (p->next->next)
        p = p->next;
    p->next = 0;
}