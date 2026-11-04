// ?ShellMusic@@YAXD@Z @ rva 0x32ca0 (10 B code + 6 B 8d9b pad) —
// mov al,[esp+4] / a2 moffs byte store / ret.  Plain C emits the a2 moffs
// byte-store form directly (probe w16c_1 exact; naked variant identical).
extern char shellMusicOn;

void ShellMusic(char on)
{
    shellMusicOn = on;
}