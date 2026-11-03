extern void __stdcall G_UHline(int l, int r, int y);
extern int clipTop, clipBottom, clipLeft, clipRight;
__declspec(naked) void __stdcall w32G_95b40_v5(int l, int r, int y)
{
	__asm {
		push esi
		mov eax, clipTop
		mov esi, [esp+10h]
		cmp eax, esi
		jg Lret
		mov eax, clipBottom
		cmp eax, esi
		jl Lret
		mov eax, clipLeft
		mov edx, [esp+8]
		cmp eax, edx
		jle L1
		mov edx, eax
L1:		mov ecx, clipRight
		mov eax, [esp+0Ch]
		cmp ecx, eax
		jge L2
		mov eax, ecx
L2:		cmp eax, edx
		jl Lret
		push esi
		push eax
		push edx
		call G_UHline
Lret:	pop esi
		ret 0Ch
	}
}
