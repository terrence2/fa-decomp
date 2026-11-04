/* 0x84920 (unnamed, 64 B): fastcall ushort id; linear search over
 * _objControlledBy[] words up to _numComputers; return idx or -1. */
extern int _numComputers;      /* 0x4e7604 */
extern unsigned short _objControlledBy[];   /* 0x4e7610 */

int __fastcall w38a_84920(unsigned short id)
{
    unsigned short *sp = _objControlledBy;
    int i;
    int n = _numComputers;
    if (id == 0)
        return -1;
    for (i = 0; i < n; i++) {
        if (sp[i] == id)
            return i;
    }
    return -1;
}
