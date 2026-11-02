/* Ui64toa - FA rva 0xe20a0 (925856) - EXACT probe verdict, tier1_a_r2.json entry 'Ui64toa_v1'
 * Form: patch-hybrid
 * Levers: 5 1-byte patches over plain C
 * Maps: _x64toa_5@20=$FA$_t_4e2000
 * patch 0xc: ->54
 * patch 0xe: ->0c
 * patch 0x11: ->4c
 * patch 0x13: ->14
 * patch 0x16: ->52
 * Probes: v1
 */
extern void __stdcall x64toa_5(unsigned long lo, unsigned long hi, char *str, int radix, int neg);

char *__cdecl _ui64toa(unsigned __int64 val, char *str, int radix)
{
    x64toa_5(*(unsigned long *)&val, *((unsigned long *)&val + 1), str, radix, 0);
    return str;
}
