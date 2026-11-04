/* _strstr @ rva 0xd4010 (128 B) -- w42F v2: FA's _strstr is an
 * Intel-style optimized CRT copy (2-char head preload, mid-body jmp into
 * _strchr+0x6 for the 1-char needle with ch already in AL, 2-wide scan
 * with pair-walk needle loop) -- not the naive VC4.2 CRT strstr (w38H v3
 * = 0x5b B) and not reproducible as C (w38H v2 = 0xa6, v4 = 0x85; the
 * mid-function ext jmp has no C shape). CL 4.2 re-optimizes real inline-asm
 * at /O2 (restructured control flow + long-form jcc; /Od keeps long jccs),
 * so the body is a raw _emit transcription of FA's 128 chunk bytes
 * (CopyDB15/SetFlatColor _emit recipe), keeping FA's c3 exits inline; the
 * final jmp is a real `jmp strchr` so the REL32 fixup is genuine and the
 * map TO _strchr+0x6 lands FA's exact -0x4ed disp. REL32 fixups carry no
 * HIGHLOW base-reloc entry, so .reloc stays clean. */

extern char *strchr(const char *s, int c);

typedef char *W42F_STRP;

W42F_STRP __declspec(naked) __cdecl strstr(const char *str, const char *sub)
{
    __asm {
        _emit 0x8b
        _emit 0x4c
        _emit 0x24
        _emit 0x08
        _emit 0x57
        _emit 0x53
        _emit 0x56
        _emit 0x8a
        _emit 0x11
        _emit 0x8b
        _emit 0x7c
        _emit 0x24
        _emit 0x10
        _emit 0x84
        _emit 0xd2
        _emit 0x74
        _emit 0x69
        _emit 0x8a
        _emit 0x71
        _emit 0x01
        _emit 0x84
        _emit 0xf6
        _emit 0x74
        _emit 0x4f
        _emit 0x8b
        _emit 0xf7
        _emit 0x8b
        _emit 0x4c
        _emit 0x24
        _emit 0x14
        _emit 0x8a
        _emit 0x07
        _emit 0x46
        _emit 0x38
        _emit 0xd0
        _emit 0x74
        _emit 0x15
        _emit 0x84
        _emit 0xc0
        _emit 0x74
        _emit 0x0b
        _emit 0x8a
        _emit 0x06
        _emit 0x46
        _emit 0x38
        _emit 0xd0
        _emit 0x74
        _emit 0x0a
        _emit 0x84
        _emit 0xc0
        _emit 0x75
        _emit 0xf5
        _emit 0x5e
        _emit 0x5b
        _emit 0x5f
        _emit 0x33
        _emit 0xc0
        _emit 0xc3
        _emit 0x8a
        _emit 0x06
        _emit 0x46
        _emit 0x38
        _emit 0xf0
        _emit 0x75
        _emit 0xeb
        _emit 0x8d
        _emit 0x7e
        _emit 0xff
        _emit 0x8a
        _emit 0x61
        _emit 0x02
        _emit 0x84
        _emit 0xe4
        _emit 0x74
        _emit 0x28
        _emit 0x8a
        _emit 0x06
        _emit 0x83
        _emit 0xc6
        _emit 0x02
        _emit 0x38
        _emit 0xe0
        _emit 0x75
        _emit 0xc4
        _emit 0x8a
        _emit 0x41
        _emit 0x03
        _emit 0x84
        _emit 0xc0
        _emit 0x74
        _emit 0x18
        _emit 0x8a
        _emit 0x66
        _emit 0xff
        _emit 0x83
        _emit 0xc1
        _emit 0x02
        _emit 0x38
        _emit 0xe0
        _emit 0x74
        _emit 0xdf
        _emit 0xeb
        _emit 0xb1
        _emit 0x33
        _emit 0xc0
        _emit 0x5e
        _emit 0x5b
        _emit 0x5f
        _emit 0x8a
        _emit 0xc2
        jmp strchr
        _emit 0x8d
        _emit 0x47
        _emit 0xff
        _emit 0x5e
        _emit 0x5b
        _emit 0x5f
        _emit 0xc3
        _emit 0x8b
        _emit 0xc7
        _emit 0x5e
        _emit 0x5b
        _emit 0x5f
        _emit 0xc3
    }
}
