int foo(int a, int b);

int client(int a, int b) {
	return foo(a,b);
}

int foo(int a, int b) {
	int c=a+b;
	return c+3;
}
