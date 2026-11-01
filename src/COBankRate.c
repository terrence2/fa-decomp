// _COBankRate@0 @ rva 0x76f60 (64 B) — FA asm: push ebx / a0 mov al,[curThing]
// / cmp al,4 / jne; taken: call COBrv / movsx esi,[eax+2] / cmp esi,0xb4 /
// jge -> 0xb8 7f 00 (0x7fff), else lea chain esi*182 (lea 9r, x5, +91r, x2,
// lea eax,[esi+esi] with zero disp32) — CL 4.2 reproduced the whole schedule
// from plain C (probe b17c_cobankrate_v1 byte-exact, incl. the lea chain and
// 66-reg ordering). movsx curThingType+0x5f word on the fall-through. Addend
// +0x5f lives in the C expression; curThing/curThingType/COBrv@0 are identity.
extern char curThing[];
extern char curThingType[];
extern int __stdcall COBrv(void);

int __stdcall COBankRate(void)
{
    if (*(unsigned char *)&curThing == 4) {
        int r = *(short *)((char *)COBrv() + 2);
        if (r >= 0xb4) return 0x7fff;
        return r * 182;
    }
    return *(short *)(curThingType + 0x5f);
}