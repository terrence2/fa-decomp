/* w46H wave-46 batch H: whole-body transplant husk for FA rva 0x7f1a0
 * (_AddCampaignPlane, 213 B code + 11 B census tail 8d642400 + 8da424..).
 * CL output is discarded by the fitobj rebuild; husk must merely keep a
 * .text section alive (non-static, else /O2 drops the TU body).
 *
 * Semantics: for n = arg0 (ebx = [esp+0xc]) downto 1: scan entries at
 * _campaignPilot+0xdb0, stride 0xbc, end at _campaignPilot+0x1c60, for
 * word[entry+0xe]==0. If found: rep stosd zero 0x2f dwords; word[entry+0x7e]
 * = 0xff00; two inline strcpy constructs (f2 ae repnz scas + rep movsd/movsb
 * pairs at 0x47f1e5..0x47f260): copy arg1 string to entry, copy the string
 * at ?hintHndl@@3PAUT_HANDLE@@A+0x19c into the second destination; word[+0xe]
 * = 1. jb-strided scan loop (jl 0x47f1c9) with self-jmp at +0x2b.
 */
int w46h_addcampaignplane_stub(void) { return 0; }