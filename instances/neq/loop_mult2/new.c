int foo(int a, int b) {
	int c = 0;
	for (int i=0; i<a; ++i)
		c += b;
	return c;}

int client(int x) {
    foo(5,5);
	return foo(5,5);
	}
