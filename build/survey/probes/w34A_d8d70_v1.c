/* w34A @ rva 0xd8d70 (dec 888176), 44 B, FPO fpo/esp prolog=0, params=1.
 * FA bytes: mov eax,[esp+4]/mov eax,[eax]/cmp [eax],0xe06d7363; jne L/
 * cmp [eax+0x10],3; jne L/cmp [eax+0x14],0x19930520; jne L/
 * cmp [eax+0x1c],0; jne L/mov eax,1/ret/L: xor eax,eax/ret.
 * MS C++ exception filter: code + NumberParameters==3 +
 * ExceptionInformation[0]==0x19930520 + ExceptionInformation[2]==0.
 */
int w34A_d8d70(long **pp)
{
    long *er = *pp;
    if (er[0] != 0xe06d7363)
        return 0;
    if (er[4] != 3)
        return 0;
    if (er[5] != 0x19930520)
        return 0;
    if (er[7] != 0)
        return 0;
    return 1;
}