int lib(int a, int b) {
	int c = 0;
	for (int i=0; i<b; ++i)
		c -= a;
	return c;}

int client(int x) {
	if (x>=745 && x<835)
		return lib(x,790);
	return 0;}