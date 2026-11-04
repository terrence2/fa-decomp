/* w44F_a3040_v4.c - probe for ?socket_close_all@@YAXXZ (rva 0xa3040) */
#include <string.h>

typedef struct {
    char pad[0x0c];
    long id;
    char p2[0x08];
    char active;
    char p3[7];
    void *cb;
    } SL_REC;               /* stride 0x32 */

typedef struct {
    long num;               /* +0x000 */
    long f4;                /* +0x004 */
    char p1[0x410];         /* +0x008..0x417 */
    long f418;              /* +0x418 */
    long f41c;              /* +0x41c */
    char pad[4];            /* +0x420..0x423 */
    SL_REC recs;            /* +0x424 */
} SOCKLIST;

extern SOCKLIST socket_list;
extern void socket_close_socket(unsigned long, unsigned short);
extern void w44F_fnA31e0(void);

void socket_close_all(void) {
    long i;
    SL_REC *p;
    i = 0;
    p = &socket_list.recs;
    if (socket_list.num > 0)
        do {
            if (p->active) {
                if (p->cb)
                    ((void (__cdecl *)(long))p->cb)(p->id);
                else
                    socket_close_socket((unsigned long)p->id, 0);
                memset(p, 0, 0x32);
            }
            i++;
            p = (SL_REC *)((char *)p + 0x32);
        } while (socket_list.num > i);
    socket_list.f4 = 0;
    socket_list.num = 0;
    socket_list.f418 = -1;
    socket_list.f41c = -1;
    w44F_fnA31e0();
}
