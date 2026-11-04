/* ?net_write_output_q@@YAXH@Z @ rva 0xadb20 (112 B) -- v3: v2's goto
 * spelling kept (je-to-call polarity matched); CL's equal-length reg-role
 * diffs (entry ptr in EAX/ECX/EDX vs FA's plan and the arg push order)
 * are patch-corrected; provenance in w36H_final.json. */
extern char player_list[];
extern char __cdecl w36h_nwoq(void *fd, void *s, long n);
extern void w36h_sbwf(void);

void net_write_output_q(int a1)
{
    char *q;
    long *s;
    long n;

    s = (long *)(*(long **)(&player_list[0x66 + a1 * 4]));
    q = (char *)s;
    s = (long *)(q + 0x2c86);
    if (*s > s[1])
        goto B1;
    n = s[2] - s[1];
    if (s[3] > n) {
        if (w36h_nwoq((void *)*(long **)q, s, n) == 0)
            return;
    }
B1:
    n = s[3];
    if (n == 0)
        goto BW;
    if (w36h_nwoq((void *)*(long **)q, s, n) == 0)
        return;
    if (s[3])
        return;
BW:
    w36h_sbwf();
}