/* w41D 0x60200 v2 — no d local; deref twice, polarity if-form, deref as
 * plain pointer-typed arg (no cast) to steer the push spellings.
 */
#include <string.h>
extern char wingIds[];
extern void *curPalette[];
extern int __cdecl CompareMemory_f(void *, void *, unsigned long);
extern void __stdcall MenuCreateRemaps_f(void);

void w41D_60200(void)
{
    if (CompareMemory_f(*(void **)(wingIds + 0x1b8), curPalette, 0x300) != 0) {
        memcpy(*(void **)(wingIds + 0x1b8), curPalette, 0x300);
        MenuCreateRemaps_f();
    }
}