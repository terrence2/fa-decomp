/* FA chunk ?net_free_player_list@@YAXXZ rva 0xaeb40 (64 B) — wave 33 batch E
   probe v2. NULLs each UNET_PLAYER_LIST ptrs[] entry (fastcall MMFreePtr
   takes the loaded VALUE in ecx; the slot is zeroed separately with an
   imm32 store), then zeroes a/count/c. Pointer base spelled as an interior
   char* delta on &player_list (0x66) so no struct-layout CSE sneaks in. */
struct UNET_PLAYER_LIST { int a; int count; int c; char pad[0x66 - 0xc]; };
extern UNET_PLAYER_LIST player_list;

extern void __fastcall MMFreePtr(void *p);

void __cdecl net_free_player_list(void)
{
    int i;
    void **p;
    i = 0;
    p = (void **)((char *)&player_list + 0x66);
    while (player_list.count > i)
    {
        MMFreePtr(*p);
        p++;
        i++;
        p[-1] = 0;
    }
    player_list.a = 0;
    player_list.c = 0;
    player_list.count = 0;
}