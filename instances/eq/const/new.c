int foo(int a, int b);


int client(int a, int b) {
	return foo(a,b);
}

int foo(int a, int b) {
	const int d=3;
	int c=b+a;
	return c+d;
}
