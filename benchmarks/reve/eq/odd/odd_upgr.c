extern int __inlineCall(int);

int lib(int x) {
	return (x+1) % 2;
}

int client(int x){
  int ret;
	if (__inlineCall(lib(x))==0){
	   	ret = 1;
	}else{
		ret = 0;
	}
  return ret;
}
