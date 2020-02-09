extern int __inlineCall(int);

int lib(int x) {
  int ret;
	if (x < 0){
		ret = -x;
	}else{
		ret = x;
	}
  return ret;
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
