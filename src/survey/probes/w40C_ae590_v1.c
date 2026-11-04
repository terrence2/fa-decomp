/* wave-40C probe v1: net_mung_name (0xae590, 96 B) */
extern char w40c_sfe8[];   /* ?state_funcs_list@@..+0xe8 = VA 0x5080e0 */
extern char w40c_sfdc[];   /* +0xdc = VA 0x5080d4 */
extern char w40c_items88[];/* _items+0x88 = VA 0x577e65 */
extern char w40c_plist1d[];/* ?player_list@@..+0x1d = VA 0x4eaa80 */

int _Sprintf(char *, ...);
char *_strncat(char *, const char *, int);

void net_mung_name(char *buf, int unused)
{
    _Sprintf(buf, w40c_sfdc, w40c_sfe8);
    _strncat(buf, w40c_items88, 0x1e);
    strcat(buf, w40c_plist1d);
}