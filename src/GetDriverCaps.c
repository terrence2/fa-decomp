// ?GetDriverCaps@CDirDraw@@QAEPBU_DDCAPS@@XZ @ rva 0x1dd00 (32 B) —
// thiscall body reading ecx: mov eax,[ecx+0x27c]; test; jne over the
// xor-eax ret0 (success branch forward, MMAllocPtr polarity);
// lea eax,[ecx+0x13c] return. Fastcall 1-param decl puts the object in
// ecx (probe w14a_gdc1, byte-exact, plain C).
struct _DDCAPS;

struct _DDCAPS * __fastcall GetDriverCaps(void *t)
{
    if (*(void **)((char *)t + 0x27c) == 0)
        return 0;
    return (struct _DDCAPS *)((char *)t + 0x13c);
}