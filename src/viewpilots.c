// _ViewPilots (FA sym __ViewPilots@0) @ rva 0x7eae0 (16 B) — fastcall thunk
//   mov ecx,2 / jmp @PilotScreen@4
extern int __fastcall PilotScreen(int);

void __stdcall _ViewPilots(void)
{
    PilotScreen(2);
}
