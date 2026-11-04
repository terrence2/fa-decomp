/* unnamed 0x32320 (and twin 0x50a80, byte-identical): fastcall add-entry
   into a growlist: [entry]=count(limit 10), slot entry+cnt*18+4 = name,
   strcpy slot+8 = str. ebp frame; inline strlen+copy. */
#include <string.h>

void __fastcall w44acNameAdd(char *entry, long n, char *name, char *str)
{
    long cnt;
    char *dst;

    if (n-- > 0) {
        do {
            cnt = *(long *)entry;
            if (cnt == 10)
                break;
            dst = entry + cnt * 18 + 4;
            *(long *)entry = cnt + 1;
            *(char **)dst = name;
            strcpy(dst + 4, str);
        } while (n-- > 0);
    }
}