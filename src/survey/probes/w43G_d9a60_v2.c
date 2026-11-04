// Whole-body naked transcription of FA chunk 0xd9a60 (163 B) (wave-41F/w42F recipe):
// every byte its own _emit line, so CL emits the FA instruction stream verbatim.
// Abs disp dwords patched to delta payloads with DIR32 newsites; baked e8 rel32s
// stay literal (chunk lands at the FA VA so raw rel displacements are correct).
void __declspec(naked) _mbsnbcpy(void)
{
    __asm {
        /* +0x00 */ _emit 0x83
                   _emit 0x3d
                   _emit 0xac
                   _emit 0xa7
                   _emit 0x51
                   _emit 0x00
                   _emit 0x00
                   _emit 0x53
                   _emit 0x56
                   _emit 0x8b
                   _emit 0x74
                   _emit 0x24
                   _emit 0x0c
                   _emit 0x57
                   _emit 0x55
                   _emit 0x8b
        /* +0x10 */ _emit 0xee
                   _emit 0x75
                   _emit 0x18
                   _emit 0x8b
                   _emit 0x5c
                   _emit 0x24
                   _emit 0x1c
                   _emit 0x8b
                   _emit 0x7c
                   _emit 0x24
                   _emit 0x18
                   _emit 0x53
                   _emit 0x57
                   _emit 0x56
                   _emit 0xe8
                   _emit 0x2d
        /* +0x20 */ _emit 0x9c
                   _emit 0xff
                   _emit 0xff
                   _emit 0x83
                   _emit 0xc4
                   _emit 0x0c
                   _emit 0x5d
                   _emit 0x5f
                   _emit 0x5e
                   _emit 0x5b
                   _emit 0xc3
                   _emit 0x6a
                   _emit 0x19
                   _emit 0xe8
                   _emit 0xde
                   _emit 0xd6
        /* +0x30 */ _emit 0xff
                   _emit 0xff
                   _emit 0x8b
                   _emit 0x7c
                   _emit 0x24
                   _emit 0x1c
                   _emit 0x8b
                   _emit 0x5c
                   _emit 0x24
                   _emit 0x20
                   _emit 0x83
                   _emit 0xc4
                   _emit 0x04
                   _emit 0xb9
                   _emit 0x04
                   _emit 0x00
        /* +0x40 */ _emit 0x00
                   _emit 0x00
                   _emit 0x85
                   _emit 0xdb
                   _emit 0x74
                   _emit 0x28
                   _emit 0x4b
                   _emit 0x8a
                   _emit 0x07
                   _emit 0x33
                   _emit 0xd2
                   _emit 0x8a
                   _emit 0xd0
                   _emit 0x84
                   _emit 0x8a
                   _emit 0xa9
        /* +0x50 */ _emit 0xa6
                   _emit 0x51
                   _emit 0x00
                   _emit 0x74
                   _emit 0x3c
                   _emit 0x88
                   _emit 0x06
                   _emit 0x47
                   _emit 0x46
                   _emit 0x85
                   _emit 0xdb
                   _emit 0x74
                   _emit 0x40
                   _emit 0x8a
                   _emit 0x07
                   _emit 0x4b
        /* +0x60 */ _emit 0x88
                   _emit 0x06
                   _emit 0x8b
                   _emit 0xd6
                   _emit 0x46
                   _emit 0x47
                   _emit 0x84
                   _emit 0xc0
                   _emit 0x75
                   _emit 0xd8
                   _emit 0xc6
                   _emit 0x46
                   _emit 0xfe
                   _emit 0x00
                   _emit 0x8b
                   _emit 0xc3
        /* +0x70 */ _emit 0x4b
                   _emit 0x85
                   _emit 0xc0
                   _emit 0x74
                   _emit 0x0b
                   _emit 0xc6
                   _emit 0x06
                   _emit 0x00
                   _emit 0x46
                   _emit 0x8b
                   _emit 0xc3
                   _emit 0x4b
                   _emit 0x85
                   _emit 0xc0
                   _emit 0x75
                   _emit 0xf5
        /* +0x80 */ _emit 0x6a
                   _emit 0x19
                   _emit 0xe8
                   _emit 0xf9
                   _emit 0xd6
                   _emit 0xff
                   _emit 0xff
                   _emit 0x83
                   _emit 0xc4
                   _emit 0x04
                   _emit 0x8b
                   _emit 0xc5
                   _emit 0x5d
                   _emit 0x5f
                   _emit 0x5e
                   _emit 0x5b
        /* +0x90 */ _emit 0xc3
                   _emit 0x88
                   _emit 0x06
                   _emit 0x8b
                   _emit 0xd6
                   _emit 0x46
                   _emit 0x47
                   _emit 0x84
                   _emit 0xc0
                   _emit 0x75
                   _emit 0xa7
                   _emit 0xeb
                   _emit 0xd1
                   _emit 0xc6
                   _emit 0x46
                   _emit 0xff
        /* +0xa0 */ _emit 0x00
                   _emit 0xeb
                   _emit 0xcb
    }
}
