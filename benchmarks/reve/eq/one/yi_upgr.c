extern int __inlineCall(int);

/*
 * Yi's example in klee
 */

int lib(int x){
  int ret;
	if (x > 10)
		ret = 12;
	else
		ret = x+1;
  return ret;
}

int client(int x){
  int ret;
	if (x > __inlineCall(lib(x)))
		ret = x;
	else
		ret = __inlineCall(lib(x));
  return ret;
}

