/* w46H wave-46 batch H: whole-body transplant husk for FA rva 0x74ff0
 * (_WinMain@16 fpo, 87 B code + 9 B census tail 8bff + 8da424..). CL output
 * is discarded by the fitobj rebuild; husk must merely keep a .text section
 * alive (non-static, else /O2 drops the TU body).
 *
 * Semantics: InitApplication(hinst) -> return 0 on fail (ret 0x10). Cache
 * __imp__GetMessageA in esi and __imp__DispatchMessageA in edi (a1/8b0d
 * moffs loads at +0x22/+0x28, both IAT DIR32 sites). Loop: GetMessageA(&msg,
 * 0,0,0); ==0 -> return [esp+0x10] (wParam chain, ret 0x10); ==-1 -> loop;
 * else DispatchMessageA(&msg). Classic wave-30 56 57 prolog band.
 */
int w46h_winmain_stub(void) { return 0; }