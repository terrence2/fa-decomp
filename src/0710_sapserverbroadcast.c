/* w46B_sapbcast_v2 - steering: negate if (init in then-branch => jne forward to convert),
 * packed SAIPX (#pragma pack(1): family@0 net@2 node@6 socket@0xc), callee order (a,&sa,2,str,cancel).
 * FA store order: family, socket, net, node_dword, node_word; node stored via lea eax,[esp+6] + [eax].
 */
#pragma pack(1)
typedef struct { unsigned short sa_family; unsigned long sa_netnum;
                 unsigned char sa_nodenum[6]; unsigned short sa_socket; } SAIPX;
#pragma pack()

extern void convert_addr_usnf2ipx(SAIPX *sa, void *addr);  /* public ?convert_addr_usnf2ipx@@YAXPAUsockaddr_ipx@@PAUNET_ADDRESS@@@Z */
extern void sapbcast(unsigned int *a, SAIPX *sa, int n, char *str, int cancel); /* $FA$_t_4857f0 */

void sapserverbroadcast(unsigned int *a, void *addr, char *str, int cancel)
{
    SAIPX sa;
    if (addr == 0)
    {
        sa.sa_family = 6;
        sa.sa_socket = 0x5204;
        sa.sa_netnum = 0;
        *(unsigned long *)&sa.sa_nodenum[0] = 0xffffffff;
        *(unsigned short *)&sa.sa_nodenum[4] = 0xffff;
    }
    else
    {
        convert_addr_usnf2ipx(&sa, addr);
    }
    sapbcast(a, &sa, 2, str, cancel);
}