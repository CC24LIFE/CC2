int foo(int a, int b);

int client(int x) {
	if (x>=745 && x<835)
		return lib(x,790);
	else
	    return 0;
}

int lib(int a, int b) {
	int c=0;
	for (int i=1;i<=a;++i)
		c+=b;

	return c;
}
