extern char WNGPart(int, short *, int);
extern void MISSIONSetCheating(void);
extern char wingSizes[];
extern unsigned short playerId;
extern char playerHasWingmen;
void w33D_mim(void)
{
	if (playerId)
	{
		int out;
		if (WNGPart(playerId, &out, 0) == 1 && wingSizes[out] >= 2)
			playerHasWingmen = 1;
		else
			playerHasWingmen = 0;
		MISSIONSetCheating();
		return;
	}
	playerHasWingmen = 0;
	MISSIONSetCheating();
}