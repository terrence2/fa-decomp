// _CTEval_tgtir @ rva 0x642b0 (48 B) — tgtradar's && chain with test
// ch,0x10 (mask 0x1000).
extern char serviceTicks[];

int CTEval_tgtir(void)
{
    if (*(short *)(serviceTicks + 0x20) != 0
        && *(char *)(serviceTicks + 0xe8) != 0
        && (*(long *)(*(long *)(serviceTicks + 0xf4) + 0xde) & 0x1000))
        return 1;
    return 0;
}