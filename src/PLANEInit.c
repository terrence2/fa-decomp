// _PLANEInit@0 @ rva 0x9b530 (16 B) — mov word [_numPlanes],0 / ret.
extern unsigned short numPlanes[];

void PLANEInit(void)
{
    *numPlanes = 0;
}