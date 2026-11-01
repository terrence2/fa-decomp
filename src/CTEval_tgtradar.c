// _CTEval_tgtradar @ rva 0x64270 (48 B) — && chain (all three je's go to
// the one shared xor-eax/ret block, w14a_ct1b): word gate serviceTicks+0x20
// == 0, byte gate serviceTicks+0xe8 == 0 (mov al/test al), dword at
// *serviceTicks+0xf4 + 0xde tested via test ch,0x8 (mask 0x800 folded into
// the high byte; a scalar-expression C form compiles to and+shr instead).
extern char serviceTicks[];

int CTEval_tgtradar(void)
{
    if (*(short *)(serviceTicks + 0x20) != 0
        && *(char *)(serviceTicks + 0xe8) != 0
        && (*(long *)(*(long *)(serviceTicks + 0xf4) + 0xde) & 0x800))
        return 1;
    return 0;
}