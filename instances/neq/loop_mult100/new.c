int lib(int a, int b) {
	int c = 0;
	for (int i=0; i<a; ++i)
		c += b;
	return c;}

int client(int x) {
	if (x>=85 && x<115)
		return lib(x,100);
	return 0;}