// @OBJGet@4 @ rva 0x8f3a0 (16 B) — and ecx,0xffff / mov eax,[ecx*4+_objPtrs]
//   / ret — indexed read of the object-pointer table.
extern long objPtrs[];

long __fastcall OBJGet(int a)
{
    return objPtrs[a & 0xffff];
}