# define NUMPRIMES 8
/*static const unsigned int primes[8] = {
        2,     3,     5,     7,    11,    13,    17,    19};*/
# define FALSE 0
# define TRUE 1

extern int __inlineCall(int);

int lib(int x, int b) {
  int ret = 1;
  int primes[8] = {
        2,     3,     5,     7,    11,    13,    17,    19};
  if (b == 0) {
    ret = 0;
  }
  else{
    int done = FALSE;
    for (int i = 0; i < NUMPRIMES; i++) {
      int mod = x % primes[i];
      if (!done && mod == 0) {
        ret = 0;
        done = TRUE;
      }
    }
  }
  return ret;
}

int client(int x){
  int ret;
  if (x < 19) {
    ret = lib(20, 1);
  } else { ret = __inlineCall(lib(x,1));
  }
  return ret;
}
