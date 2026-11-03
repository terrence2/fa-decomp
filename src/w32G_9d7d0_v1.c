int __fastcall w32G_9d7d0(int b, int v)
{
	int d = v - b;
	int r = b + d / 5;
	if (r < 0x4b)
		r = b + d / 2;
	return r;
}
