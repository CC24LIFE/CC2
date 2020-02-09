extern int __inlineCall(int);


int lib(int x) {
	int counter = 0;
	while (x < 0) {
		x++;
		counter++;
	}
	return counter;
}

int client(int x){
  int ret;
	if (x > 0) {
		ret = -__inlineCall(lib(-x));
	}else{
		ret = __inlineCall(lib(x));
	}
  return ret;
}

