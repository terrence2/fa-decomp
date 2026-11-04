// Whole-body naked transcription of FA chunk 0xd91c0 (161 B) (wave-41F/w42F recipe):
// every byte its own _emit line, so CL emits the FA instruction stream verbatim.
// Abs disp dwords patched to delta payloads with DIR32 newsites; baked e8 rel32s
// stay literal (chunk lands at the FA VA so raw rel displacements are correct).
void __declspec(naked) _freeptd(void)
{
    __asm {
        /* +0x00 */ _emit 0x83
                   _emit 0x3d
                   _emit 0x20
                   _emit 0xa5
                   _emit 0x51
                   _emit 0x00
                   _emit 0xff
                   _emit 0x56
                   _emit 0x0f
                   _emit 0x84
                   _emit 0x91
                   _emit 0x00
                   _emit 0x00
                   _emit 0x00
                   _emit 0x8b
                   _emit 0x74
        /* +0x10 */ _emit 0x24
                   _emit 0x08
                   _emit 0x85
                   _emit 0xf6
                   _emit 0x75
                   _emit 0x12
                   _emit 0xa1
                   _emit 0x20
                   _emit 0xa5
                   _emit 0x51
                   _emit 0x00
                   _emit 0x50
                   _emit 0xff
                   _emit 0x15
                   _emit 0x84
                   _emit 0xa6
        /* +0x20 */ _emit 0x58
                   _emit 0x00
                   _emit 0x8b
                   _emit 0xf0
                   _emit 0x85
                   _emit 0xf6
                   _emit 0x74
                   _emit 0x69
                   _emit 0x8b
                   _emit 0x46
                   _emit 0x24
                   _emit 0x85
                   _emit 0xc0
                   _emit 0x74
                   _emit 0x09
                   _emit 0x50
        /* +0x30 */ _emit 0xe8
                   _emit 0x3b
                   _emit 0xef
                   _emit 0xff
                   _emit 0xff
                   _emit 0x83
                   _emit 0xc4
                   _emit 0x04
                   _emit 0x8b
                   _emit 0x46
                   _emit 0x28
                   _emit 0x85
                   _emit 0xc0
                   _emit 0x74
                   _emit 0x09
                   _emit 0x50
        /* +0x40 */ _emit 0xe8
                   _emit 0x2b
                   _emit 0xef
                   _emit 0xff
                   _emit 0xff
                   _emit 0x83
                   _emit 0xc4
                   _emit 0x04
                   _emit 0x8b
                   _emit 0x46
                   _emit 0x30
                   _emit 0x85
                   _emit 0xc0
                   _emit 0x74
                   _emit 0x09
                   _emit 0x50
        /* +0x50 */ _emit 0xe8
                   _emit 0x1b
                   _emit 0xef
                   _emit 0xff
                   _emit 0xff
                   _emit 0x83
                   _emit 0xc4
                   _emit 0x04
                   _emit 0x8b
                   _emit 0x46
                   _emit 0x38
                   _emit 0x85
                   _emit 0xc0
                   _emit 0x74
                   _emit 0x09
                   _emit 0x50
        /* +0x60 */ _emit 0xe8
                   _emit 0x0b
                   _emit 0xef
                   _emit 0xff
                   _emit 0xff
                   _emit 0x83
                   _emit 0xc4
                   _emit 0x04
                   _emit 0x8b
                   _emit 0x46
                   _emit 0x40
                   _emit 0x85
                   _emit 0xc0
                   _emit 0x74
                   _emit 0x09
                   _emit 0x50
        /* +0x70 */ _emit 0xe8
                   _emit 0xfb
                   _emit 0xee
                   _emit 0xff
                   _emit 0xff
                   _emit 0x83
                   _emit 0xc4
                   _emit 0x04
                   _emit 0x8b
                   _emit 0x46
                   _emit 0x44
                   _emit 0x85
                   _emit 0xc0
                   _emit 0x74
                   _emit 0x09
                   _emit 0x50
        /* +0x80 */ _emit 0xe8
                   _emit 0xeb
                   _emit 0xee
                   _emit 0xff
                   _emit 0xff
                   _emit 0x83
                   _emit 0xc4
                   _emit 0x04
                   _emit 0x56
                   _emit 0xe8
                   _emit 0xe2
                   _emit 0xee
                   _emit 0xff
                   _emit 0xff
                   _emit 0x83
                   _emit 0xc4
        /* +0x90 */ _emit 0x04
                   _emit 0x6a
                   _emit 0x00
                   _emit 0xa1
                   _emit 0x20
                   _emit 0xa5
                   _emit 0x51
                   _emit 0x00
                   _emit 0x50
                   _emit 0xff
                   _emit 0x15
                   _emit 0x70
                   _emit 0xa6
                   _emit 0x58
                   _emit 0x00
                   _emit 0x5e
        /* +0xa0 */ _emit 0xc3
    }
}
