// _SeqEnd @ rva 0x45450 (64 B) — FA asm: 33 c0/56/57/8b f3/8b fe (walk
//   seqList stride 0x38 to &useMixer, SeqStop(i) for non-zero heads)/
//   e8 ?SoundAllOff@@YIXXZ/e8 ?MusicOff@@YIXXZ/6a 04/e8 _RMFreeAllId@4/
//   5e 5f c9 c3.  Plain C wins, including the 56 57 save order.
//   Probe build/w4probe/b17_seqend_v1.c — exact modulo fixup dwords.

extern char seqList[];
extern char useMixer;

void __cdecl SeqStop(int n);
void __fastcall SoundAllOff(void);
void __fastcall MusicOff(void);
void __stdcall RMFreeAllId(int id);

void SeqEnd(void) {
    int i = 0;
    char *p = seqList;
    do {
        if (*p)
            SeqStop(i);
        p += 0x38;
        i++;
    } while (p < &useMixer);
    SoundAllOff();
    MusicOff();
    RMFreeAllId(4);
}