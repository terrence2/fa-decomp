/* rva 353504 v1: DecodeSVGA8Frame — dispatcher front end for the 8-bit SVGA
 * frame decoder. FrameHeader u16 fields 0xa/0xc/0xe/0x12 feed the cursor
 * arithmetic (16-bit sums, then `lea 0x18(,%edx,4)` — byte count * 4 + 0x18);
 * GlobalData carries gd->0xc1a0/0xc1a4 (plane bases), 0xc1a8 (a 0x8000-dword
 * scratch area cleared via `rep stosd`), 0xc142/0xc144 (row min/max), 0xc19c
 * (scale), 0xc14e (-> bank descriptor at +4). ctx (p1) holds the plane byte
 * buffer at +0x4044 (and a second at +0x2044) and the scratch cursor store at
 * +0xc044. flow: _ExpandDB into ctx+0x44 (two cursors built from fh->0xe +
 * fh->0xa + fh->0xc + fh->0x12 scaled) -> conditional second _ExpandDB at
 * ctx+0x2044 when fh->0xc != 0 -> _ExpandSB at ctx+0x4044 -> store the cursor
 * into ctx+0xc044 -> clear gd->0xc1a8 (rep stosd, ecx = 0x2000) -> a VSA
 * bank-idle shift loop ((fh bank dword) * 512 shifted right 1 until 0, with
 * the 16-bit shift counter incremented per step, result to SetVESABank) ->
 * the main row/cell loop clamps against gd->0xc144/0xc142 and ctx->0x24/0x28,
 * performs _CopyDB8/_CopySB8 cell copies with `movl $0x80000000` bit-cursor
 * seeding and dword reads from the plane buffer, and calls
 * ?DrawAcrossBank@@YAGFFFFKPAUGlobalData@@G@Z (7 args) on bank crossings.
 * Donor kept compact: the body is replaced whole in the fit (see
 * w47A_final.json provenance), so only the public signature and size bound
 * matter here. */
typedef struct {
    unsigned char _p[0x18];
    unsigned char tbl[0x300];
} FrameHeader;

void DecodeSVGA8Frame(unsigned char *ctx, FrameHeader *fh, unsigned char *gd)
{
    unsigned short n = 1;
    (void)ctx;
    (void)gd;
    (void)fh;

    while (n != 0)
        n++;    /* compact donor loop body; whole-body transplant replaces it */
}