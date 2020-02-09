int n;

int lib(int n) {
	return n  ;
}

int sum(int n) {
	 n = ident(n);

		if (n <= 1) return n;
		return n + sum(n-1);
}

int main() {
return sum(n);
}