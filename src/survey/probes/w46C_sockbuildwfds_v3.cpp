// v3: decl order (i,e,max,...) for e=esi/i=edx; ptab as array extern
//     (indexed form mov [idx*4+imm]); lvl -> ebx scratch (no ebp push).
typedef char W46CSOCK_PAD[0x2c92];

extern "C" {
extern long w46c_sln;              /* ?socket_list@@3USOCKET_STATE_LIST@@A+0x0 */
extern volatile unsigned long w46c_slcnt;   /* +0x210 */
extern unsigned long w46c_slfd[];  /* +0x214 */
extern unsigned long w46c_slit;    /* +0x424 */
extern unsigned long w46c_ptab[];  /* ?player_list@@3UNET_PLAYER_LIST@@A+0x66 */
}

void socket_build_write_fds(void)
{
    long i;
    char *e;
    unsigned long max, id, lvl;

    i = 0;
    e = (char *)&w46c_slit;
    w46c_slcnt = 0;
    if (i < w46c_sln) {
        max = 0x40;
        do {
            if (*(unsigned char *)(e + 0x18) != 0) {
                id = *(long *)e;
                if (id != -1) {
                    lvl = *(unsigned long *)(w46c_ptab[id] + 0x2c92);
                    if ((long)lvl > 0) {
                        if (w46c_slcnt < max) {
                            w46c_slfd[w46c_slcnt] = *(long *)(e + 0xc);
                            w46c_slcnt++;
                        }
                    }
                }
            }
            i++;
            e += 0x32;
        } while (i < w46c_sln);
    }
}