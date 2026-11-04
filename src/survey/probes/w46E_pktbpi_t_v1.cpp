// Transplant husk (whole-body patch) for ?pkt_build_player_info@@YAXPAUNET_PKT@@GPAUNET_PLAYER_LIST@@@Z,
// rva 380608 (0x5cec0), 176 B.
// FA semantics (dis.py 0x5cec0): cdecl, (p=arg0 u16?, l, list):
//   pkt_set_header(-1, p, (short)arg0w);   // push (arg0&0xffff)
//   p[?]: ebp frame; w = *(u16*)list->id; w_len_off = (w*0x38+4) 16-bit imul/add/add onto [ebx+4]
//   for (i = 0; i < list->count; i++) {    // player_list+0x66 loop base (0x577eae = ?player_list+0x66)
//     pp = *(void**)(&player_list+0x66) ... walks [edx] chain: name copy =
//       strlen(*(char**)edx+8) via repnz scasb, rep movsd/movsb into ebx+0xe; ebx += 0x38
//   }
// CL 4.2 cannot reproduce the 16-bit imul/add packet-offset arithmetic in this schedule;
// body fully patched over this husk.
struct UNET_PKT { long a; };
struct UNET_PLAYER_LIST { long a; };
void pkt_build_player_info(UNET_PKT *p, unsigned short g, UNET_PLAYER_LIST *l)
{ (void)p; (void)g; (void)l; }