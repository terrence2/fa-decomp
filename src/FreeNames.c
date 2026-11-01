// _FreeNames@0 @ rva 0x1d470 — MMFreePtr(items) then items = 0 (probe d99
//   exact; the fastcall callee is FA's @MMFreePtr@4 via identity name).
extern void *items;
extern void __fastcall MMFreePtrF(void *p);

void FreeNames_q(void)
{
    MMFreePtrF(items);
    items = 0;
}
