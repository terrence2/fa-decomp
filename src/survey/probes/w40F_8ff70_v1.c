/* wave-40F probe v1: 0x8ff70 (64 B) vtbl-call wrapper with anchor init */
typedef void *(*W8FM)(void *, long, long);

extern char w40f_vt0[];    /* $FA$_t_490240 (stub anchor) */
extern char w40f_vt1[];    /* $FA$_t_4903b0 (w34E alias anchor) */
void w40f_cb(void *o);     /* $FA$_t_48ffb0 (stub) */

void __cdecl w40f_8ff70(void *o)
{
    char *r;

    r = (char *)(*(W8FM *)(*(void **)((char *)o + 4)))(o, 1, 0x18);
    *(long *)((char *)o + 0x16e) = (long)r;
    *(char **)r = w40f_vt0;
    ((char **)r)[1] = w40f_vt1;
    *(char *)(r + 8) = 0;
    w40f_cb(o);
}