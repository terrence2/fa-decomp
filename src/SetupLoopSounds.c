// ?SetupLoopSounds@@YIXXZ @ rva 0x34310 (32 B) — FA asm: mov eax,offset
//   loopSnd (b8) / xor ecx,ecx / loop: mov word [eax+0x22],cx (66 89 48 22)
//   / add eax,0x26 / cmp eax,offset mm_page_size (3d — the loop bound is the
//   ADDRESS of mm_page_size: loopSnd's 4×0x26 records end exactly where
//   mm_page_size lives) / jb loop / ret.  Clears every record's in-use word
//   (+0x22).  v1 plain C do-while with a &mm_page_size pointer bound; if CL
//   emits c7 word-store imm per iteration (no shared cx zero) or folds the
//   bound through a load, fall back to naked asm (11 code bytes either way).
//   Chunk name is FA.SMS mangled (YIXXZ), so the C fn carries the _q suffix.
extern char loopSnd[];
extern unsigned long mm_page_size;

void SetupLoopSounds_q(void)
{
    char *p;
    char *end;
    p = loopSnd;
    end = (char *)&mm_page_size;
    do {
        *(unsigned short *)(p + 0x22) = 0;
        p += 0x26;
    } while (p < end);
}