// Transplant husk (whole-body patch) for ?NewVDOLinkNode@@YAPAUVDOLinkedList@@PAD0@Z,
// rva 704432 (0xabfb0), 176 B.
// FA semantics (dis.py 0xabfb0): struct U { long v; } VDOLinkedList;
//   node = VDOAlloc(12); if (!node) { vdoExitCode = 0x1; return NULL; }
//   node->v = buf = VDOAlloc(128); if (!buf) { FreeVDOLinkNode(node); vdoExitCode=...; return NULL; }
//   node->v = buf; strncpy128(buf, sz);  (repnz scasb + not ecx; shr 2 rep movsd; and 3 rep movsb)
//   node->next = ReadFrameSizesFile(arg2) -> if (r) return node;
//   FreeVDOLinkNode(node); node = NULL; *(unsigned short*)&vdoExitCode = 3 (66 c7 05 03 00 twice)
// CL /O2 inlines the strlen+copy differently; body fully patched over this husk.
struct VDOLinkedList { long a; };
VDOLinkedList * NewVDOLinkNode(char *s, VDOLinkedList *p)
{ (void)s; (void)p; return 0; }