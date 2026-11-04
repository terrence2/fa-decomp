/* rva 0xc4e54 (_DecompressVideo@20 806484). FA: builds 0x509e86 jump table walk for video decompress (dvbuf+0x3c0 table base, dvbuf+0x3c2 dispatch). Whole-body transplant: CL husk below is a placeholder whose .text bytes are overwritten by the FA chunk via one 0-length patch band; only the 2 DIR32 reloc dwords at off 9/71 are re-baked as newsites.. */
int w46a_decvideo_stub(void) { return 0; }
