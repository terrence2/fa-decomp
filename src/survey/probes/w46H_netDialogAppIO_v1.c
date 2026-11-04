/* w46H wave-46 batch H: whole-body transplant husk for FA rva 0x52b0
 * (?netDialogAppIO@@YAJJPAD@Z cdecl, 144 B chunk, no census tail). CL output
 * is discarded by the fitobj rebuild; husk must merely keep a .text section
 * alive (non-static, else /O2 drops the TU body).
 *
 * Semantics: switch on msg[0] minus 'e' (4-entry jump table at chunk+0x80,
 * moffs disp at +0x12, 4 .reloc table-entry fixups at +0x80/+0x84/+0x88/+0x8c):
 * case 'e' -> CN_NewPrint(s); 'f'/'g' -> DoDialogInfoBox(s,1) then jmp to
 * GetKey loop at +0x23; 'h' -> DoDialogInfoBox(s,2) then return (short)ax.
 * GetKey loop: if GetKey() returns nonzero, return 1; else read mouse via
 * MOUSERead(&b,&b2) (lea [esp+3]/[esp+4]) and return (byte[esp+3]==1) via
 * sbb eax,eax / inc eax.
 */
int w46h_netdialogappio_stub(void) { return 0; }