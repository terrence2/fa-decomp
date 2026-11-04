/* wave-40C probe v2: socket_set_doa - add-if-absent store restored */
extern int w40c_sockcnt;   /* ?socket_list@@3USOCKET_STATE_LIST@@A+0x314 */
extern int w40c_arrP;      /* +0x318 (address-of target for the walker) */
extern int w40c_arrX[];    /* +0x318 (array base for the indexed store) */

void socket_set_doa(unsigned int v)
{
    int i = 0;
    int *p;
    unsigned int c;

    if (w40c_sockcnt != 0) {
        p = &w40c_arrP;
        do {
            if (*p == (int)v)
                return;
            p++;
            i++;
        } while (w40c_sockcnt > i);
    }
    c = w40c_sockcnt;
    if (c < 0x40u) {
        w40c_arrX[c] = v;
        w40c_sockcnt = c + 1;
    }
}