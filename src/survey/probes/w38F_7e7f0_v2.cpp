/* w38F_7e7f0_v2: ?CN_WriteConfig@@YAXPAUCN_INFO@@PAE@Z — fopen/write
 * checksum dword/write 0xddc bytes/fclose; mode string is a baked
 * relocated push of _fmtReduceButtonH+0x1b0 (fake extern + map).
 * v2: param swap — FA loads [esp+8] (2nd param) = path for fopen and
 * [esp+0xc] (1st param) = struct for checksum/0xddc write. */
struct CN_INFO { long pad0; };

extern "C" int __cdecl _fopen(char *, char *);
extern "C" int __cdecl _fwrite(const void *, unsigned long, unsigned long, void *);
extern "C" int __cdecl _fclose(void *);
long __cdecl CfigChecksum(CN_INFO *);
extern "C" char w38f_wb;

void CN_WriteConfig(CN_INFO *a, unsigned char *b)
{
    long sum;
    int f;
    f = _fopen((char *)b, &w38f_wb);
    if (f != 0) {
        sum = CfigChecksum((CN_INFO *)a);
        _fwrite(&sum, 4, 1, (void *)f);
        _fwrite((char *)a, 0xddc, 1, (void *)f);
        _fclose((void *)f);
    }
}