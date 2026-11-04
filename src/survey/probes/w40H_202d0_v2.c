/* w40H 0x202d0 v2 — plain long array (FA SIB = 8d, *4 stride):
 * if (_fortPlayers[idx] == -1) { _fortPlayers[idx] = val; return 1; }
 * return 0 — rest identical to v1 (mov al,1 / xor al,al / ret 8 matched). */
extern long fortPlayersW40[];

unsigned char __stdcall w40h202d0(long val, long idx)
{
	if (fortPlayersW40[idx] == -1) {
		fortPlayersW40[idx] = val;
		return 1;
	}
	return 0;
}
