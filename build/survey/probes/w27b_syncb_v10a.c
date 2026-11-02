// 0xae2a0 ?clear_all_sync_replies@@YAXX@Z (48 B) — v10a (synca-twin: reply flag +0x10/+0x39)
extern char player_list_t27[];  /* map _player_list_t27=?player_list@@3UNET_PLAYER_LIST@@A */

void __cdecl clear_all_sync_replies27(void)
{
    long z;
    long n;
    void **p;
    void *t;

    *(long *)(player_list_t27 + 0x10) = z = 0;
    n = *(long *)(player_list_t27 + 4) - 1;
    if (n < 0)
        return;
    p = (void **)(player_list_t27 + 0x66 + 4 * n);
    do {
        t = *p;
        p = p - 1;
        *(char *)((char *)t + 0x39) = (char)z;
    } while (p >= (void **)(player_list_t27 + 0x66));
}
