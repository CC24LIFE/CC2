int foo(int a, int b);

int clientmain() {
	return foo(9,500);
}

int foo (int a, int b) {
	int c=a+b;
	return c;
}
