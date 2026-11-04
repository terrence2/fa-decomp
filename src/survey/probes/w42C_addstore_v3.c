/* w42C cand2: _AddCampaignStore @0x7f320 (160 B) — cdecl 2 params. */
#include <string.h>
extern char w42c_cp[];                 /* _campaignPilot+0x1c60 */
extern long __cdecl stricmp(const char *, const char *);

struct w42c_rec { char name[14]; short len; };

long __cdecl AddCampaignStore(long v, char *name)
{
    struct w42c_rec *r;
    long i, j, n;
    short slen;

    r = (struct w42c_rec *)w42c_cp;
    for (i = 0; i < 0x32; i++) {
        if (r->len == 0 && stricmp(name, r->name) == 0)
            goto found;
        r++;
    }
    for (r = (struct w42c_rec *)w42c_cp, j = 0; j < 0x32; r++, j++) {
        if (r->len == 0) {
            n = (long)strlen(name) + 1;
            memcpy(r->name, name, n);
            r->len = (short)v;
            return n;
        }
    }
    return j;
found:
    slen = r->len;
    if (slen == 0x7fff)
        return 0;
    r->len = (short)(v + slen);
    return (long)(short)(v + slen);
}
