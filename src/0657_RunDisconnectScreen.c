// ?RunDisconnectScreen@@YGXXZ @ rva 0x7e8f0 (32 B) — cdecl CN_SetLines(0xac,
//   0xa5) (push imm pair / add esp,8 after) then the final 0-arg call
//   tail-jmps e9 to ?MP_Shutdown@@YAXXZ (Info2640Preload shape, w8_i24).
extern void __cdecl CN_SetLines(unsigned a, unsigned b);
extern void __cdecl MP_Shutdown(void);

void __stdcall RunDisconnectScreen_q(void)
{
    CN_SetLines(0xac, 0xa5);
    MP_Shutdown();
}