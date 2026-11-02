/* _RORemoveCurObj@0 @ rva 0x4b0c0 (80 B) — stdcall void(void):
   do-while scan over _ro (stride 0xa) matching word == _curId; on hit:
   *(ushort*)(cur+6) = _currentTime+5; if (_playerId == _curId) -> 0x7fff. */
extern unsigned char w28a_ro[];        /* =_ro */
extern unsigned char w28a_roEnd[];     /* =_ro+0x6d6 (scan end) */
extern unsigned short w28a_curId;      /* =_curId */
extern unsigned short w28a_curW;       /* =_currentTime */
extern unsigned short w28a_pid;        /* =_playerId */

void __stdcall w28a_RORemoveCurObj(void)
{
    unsigned char *cur = w28a_ro;
    do {
        if (*(unsigned short *)cur == w28a_curId) {
            unsigned short cid = w28a_curId;
            *(unsigned short *)(cur + 6) = w28a_curW + 5;
            if (w28a_pid == cid)
                *(unsigned short *)(cur + 6) = 0x7fff;
            return;
        }
        cur += 10;
    } while (cur < w28a_roEnd);
}
