// $FA$_t_470b10 v2 — bottom condition spelled numComputers > i to flip
// the compare direction + jcc polarity (FA: cmp ebx,eax / jl back edge;
// v1 gave cmp eax,ebx / jg).
extern long w43b_players[];    /* map _w43b_players=?mpStatus@@3PAJA */
extern long numComputers;
extern long *MP_Info_q(void);  /* map _MP_Info_q=?MP_Info@@YAPAUMP_INFO@@XZ */

typedef struct { unsigned char pad[0x158]; unsigned long bits; } W43_MPI;

char __fastcall w43b_allNotReady(long me)
{
    long i;
    W43_MPI *p;
    i = 1;
    if (numComputers > i) {
        do {
            p = (W43_MPI *)MP_Info_q();
            if (p->bits & (1 << i)) {
                if (w43b_players[i] != me)
                    return 0;
            }
            i++;
        } while (numComputers > i);
    }
    return 1;
}