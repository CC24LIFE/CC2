int lib(int x) {
   int result;
  if (x == 0)
     result = 0;
  if (x < 0)
     result = -1;
  else
     result = 1;
  return result;
}

int client(int x){
  if (x > 0) {
    return lib(x);
  }
  return x;
}

int main() {
	int x;
	return client(x);
}
