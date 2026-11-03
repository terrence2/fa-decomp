extern int __stdcall TIMESystemTime(void);
char __fastcall w32G_87020_v4(int s, int e)
{
	int now = TIMESystemTime();
	int ec;
	ec = e - s;
	if (ec == -1) goto exit1;
	for (;;) {
		if (s == now) return 0;
		s++;
		ec = e - s;
		if (ec != -1) continue;
		break;
	}
exit1:
	return 1;
}
