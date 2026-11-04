// 0xae270 ?clear_all_syncs@@YAXX@Z (48 B) — v10a (zero via first-store; n local back)
extern char player_list_t27[];  /* map _player_list_t27=?player_list@@3UNET_PLAYER_LIST@@A */

void __cdecl clear_all_syncs27(void)
{
    long z;
    long n;
    void **p;
    void *t;

    *(long *)(player_list_t27 + 0xc) = z = 0;
    n = *(long *)(player_list_t27 + 4) - 1;
    if (n < 0)
        return;
    p = (void **)(player_list_t27 + 0x66 + 4 * n);
    do {
        t = *p;
        p = p - 1;
        *(char *)((char *)t + 0x3a) = (char)z;
    } while (p >= (void **)(player_list_t27 + 0x66));
}
