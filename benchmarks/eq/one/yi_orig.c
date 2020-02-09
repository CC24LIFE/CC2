/*
 * Yi's example in klee
 */

int lib(int x){
  int ret;
	if (x > 10)
		ret = 11;
	else
		ret = x;
  return ret;
}

int client(int x){
  int ret;
	if (x > lib(x))
		ret = x;
	else
		ret = lib(x);
  return ret;
}
