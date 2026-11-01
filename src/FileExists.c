// ?FileExists@@YADPAD@Z @ rva 0xabee0 (32 B) — FA asm:
//   mov eax,[esp+4] / push eax / call _SearchLib / add esp,4 / cmp eax,-1
//   (83 f8 ff imm8 form) / setne cl / mov al,cl / ret
// char return; CL 4.2 routes the boolean through cl here (setne cl / mov
// al,cl — unlike the wave-9 dl-flag family) and folds the -1 compare into
// the imm8 form. Plain C exact (probe b18c_FileExists, round 1 — the
// surprise: no naked asm needed, the cl intermediate came out on its own).
extern int __cdecl SearchLib(char *name);

char __cdecl FileExists(char *name)
{
    return (char)(SearchLib(name) != -1);
}
