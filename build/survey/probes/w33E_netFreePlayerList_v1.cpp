/* FA chunk ?net_free_player_list@@YAXXZ rva 0xaeb40 (64 B) — wave 33 batch E
   probe v1. Steps the pointer array at player_list+0x66 calling MMFreePtr on
   each stored pointer and nulling the slot after the call; zeroes the list
   header fields (+0, +8, +4) at the end. */
struct UNET_PLAYER_LIST {
    int a;
    int count;
    int c;
    char pad[0x66 - 0xc];
    void *ptrs[2];
};
extern struct UNET_PLAYER_LIST player_list;
extern void __fastcall MMFreePtr(void *ptr);

void net_free_player_list(void)
{
    void **p;
    int i;
    i = 0;
    p = player_list.ptrs;
    while (player_list.count > i)
    {
        MMFreePtr(*p++);
        i++;
        p[-1] = 0;
    }
    player_list.a = 0;
    player_list.c = 0;
    player_list.count = 0;
}