
int lib(unsigned int x, int b) {
   int NUMPRIMES = 8;
static const unsigned int primes[8] = {
        2,     3,     5,     7,    11,    13,    17,    19};
  int result;
  int cont = 1;
  if (b == 0) {
    result =   0;
  }
  else{
    for (int i = 0; i < NUMPRIMES; i++) {
      int mod = x % primes[i];

          if (mod == 0){
           if (cont){
            result =  0;
            cont = 0;
            }
           }
    }
    if (cont){
    result =   1;
    cont = 0;
    }
  }
  return result;
}


int client(unsigned int x){
  int result;
  if (x < 19) {
    result = lib(20,1);
  }else{
  result=lib(x,1);
  }
  return result;
}

int main() {
	unsigned int x=2;
	return client(x);
}
