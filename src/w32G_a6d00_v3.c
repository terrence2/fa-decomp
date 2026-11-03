__declspec(naked) void __fastcall w32G_a6d00_v3(void)
{
	__asm {
		push ebx
		mov al, byte ptr [ecx+13h]
		mov dl, byte ptr [ecx+10h]
		mov bl, byte ptr [ecx+11h]
		or  al, dl
		mov dl, byte ptr [ecx+12h]
		or  al, bl
		or  al, dl
		jne L1
		or  byte ptr [ecx+0fh], 1
		pop ebx
		ret
L1:		or  byte ptr [ecx+0eh], 80h
		pop ebx
		ret
	}
}
