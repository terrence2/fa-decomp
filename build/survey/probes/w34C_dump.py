#!/usr/bin/env python3
"""w34C_dump.py <cl.obj> <rva>  — dump probe obj .text disasm w/ relocs + FA side-by-side"""
import sys, struct, json, subprocess, re

def parse(path):
    b = open(path, 'rb').read()
    nsec, ts, symptr, nsyms, opt = struct.unpack_from('<HIIHh', b, 2)
    off = 20 + opt
    secs = []
    for i in range(nsec):
        o = off + i*40
        name = b[o:o+8].split(b'\0')[0].decode()
        vsize, va, rawsz, rawptr = struct.unpack_from('<IIII', b, o+8)
        rptr, = struct.unpack_from('<I', b, o+24)
        nrel, = struct.unpack_from('<H', b, o+32)
        secs.append(dict(name=name, va=va, rawsz=rawsz, rawptr=rawptr,
                         rptr=rptr, nrel=nrel))
    raw = []
    strtab = b[symptr + nsyms*18:]
    i = 0
    while i < nsyms:
        z = b[symptr + i*18 : symptr + i*18 + 4]
        if z[0] == 0:
            idx = struct.unpack_from('<I', z, 1)[0]
            name = strtab[idx:].split(b'\0')[0].decode('latin-1')
        else:
            name = z.rstrip(b'\0').decode('latin-1')
        val, secnum, typ, cls, aux = struct.unpack_from('<Ihhbb', b, symptr + i*18 + 4)
        raw.append((name, val, secnum, typ, cls))
        i += 1 + max(aux, 0)
    return b, secs, raw

def main():
    path, rva = sys.argv[1], int(sys.argv[2], 0)
    b, secs, raw = parse(path)
    text = max((s for s in secs if s['name'].startswith('.text') and s['rawsz'] > 0),
               key=lambda s: s['rawsz'])
    cl = b[text['rawptr']:text['rawptr'] + text['rawsz']]
    rel = list(struct.iter_unpack('<IIh', b[text['rptr']:text['rptr'] + text['nrel']*10]))
    byoff = {}
    for va_, symidx, typ in rel:
        nm = raw[symidx][0] if symidx < len(raw) else '?'
        byoff.setdefault(va_ - text['va'], []).append((nm, typ))
    L = json.load(open('build/layout.json'))
    exe = open('FA/FA.EXE', 'rb').read()
    c = next(x for x in L['text_chunks'] if x['rva'] == rva)
    fa = exe[c['off']:c['off'] + c['size']]
    print('CL code %#x B, FA chunk %#x B' % (len(cl), len(fa)))
    with open('/tmp/w34c_dump.bin', 'wb') as t:
        t.write(cl)
    adj = 0x400000 + rva
    out = subprocess.run(['objdump', '-D', '-b', 'binary', '-m', 'i386', '-M', 'intel',
                          '--adjust-vma=%#x' % adj, '/tmp/w34c_dump.bin'],
                         capture_output=True, text=True).stdout
    for ln in out.splitlines():
        m = re.match(r'^\s*([0-9a-f]+):\s+([0-9a-f ]+?)\s{2,}(.*)$', ln)
        if not m:
            continue
        off = int(m.group(1), 16) - (0x400000 + rva)
        if off >= len(cl):
            continue
        ann = ''
        if off in byoff:
            ann = '; REL ' + ', '.join('%s(t%d)' % (n, ty) for n, ty in byoff[off])
        print('%04x: %-21s %-26s %s' % (off, m.group(2), m.group(3), ann))
    print('--- FA raw:')
    for i in range(0, len(fa), 16):
        print('  %04x %s' % (i, fa[i:i+16].hex()))

main()