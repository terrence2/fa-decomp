/* rva 350496 v1: _DecodeDSVGA8Frame — the full 8-bit SVGA frame decoder that
 * DecodeSVGA8Frame (rva 353504) dispatches into. Reads FA's global page-size
 * `_cb` fifteen times (every HIGHLOW in the chunk's .reloc entry), calls
 * _ExpandDB/_ExpandSB/_Decode8?/SetVESABank/DrawAcrossBank, and drives the
 * .data-band plane buffers. Donor kept compact: the body is replaced whole in
 * the fit (see w47A_final.json provenance; the 5 call sites become REL32
 * newsites type 20 and the 15 `_cb` pointer reads become DIR32 newsites type
 * 6, `site:6:_cb+0x0`), so only the public signature and size bound matter
 * here. */
void DecodeDSVGA8Frame(unsigned char *ctx, unsigned char *fh, unsigned char *gd)
{
    unsigned short n = 1;
    (void)ctx;
    (void)gd;
    (void)fh;

    while (n != 0)
        n++;    /* compact donor loop body; whole-body transplant replaces it */
}