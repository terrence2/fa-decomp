/* net_set_ready - FA rva 0xae110 (712976) - EXACT probe verdict, tier1_a_r1.json entry 'net_set_ready_v1'
 * Form: plain C
 * Levers: plain C; call forms auto-match
 * Maps: _netPlayerArr=?player_list@@3UNET_PLAYER_LIST@@A+0x66, _netReadyCnt=?player_list@@3UNET_PLAYER_LIST@@A+0x8
 * Probes: v1
 */
extern void *netPlayerArr[];
extern unsigned long netReadyCnt;

void net_set_ready(void *s)
{
    unsigned long id = *(unsigned long *)s;
    *(unsigned char *)((char *)netPlayerArr[id] + 0x37) = 1;
    netReadyCnt++;
}
