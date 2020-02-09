typedef struct t {
	int data;
	struct t* next;
} st;

st *my;


int lib(st *s) {
	int x = 1;
	 s -> data = x;
	return 1;
}


int client() {
	int x;
	x = f(my);
	return x < 10;
}

