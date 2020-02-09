extern int __inlineCall(int);
int lib(int x, int b)
{
  int ret = 1;
  int primes[8] = {2, 3, 5, 7, 11, 13, 17, 19};
  if (b == 0)
  {
    ret = 0;
  }
  else
  {
    int done = 0;
    for (int i = 0; i < 8; i++)
    {
      int mod = x % primes[i];
      if ((!done) && (mod == 0))
      {
        ret = 0;
        done = 1;
      }

    }

  }

  return ret;
}

int client(int x, int x_copy1, int x_copy2, int x_copy3, int x_copy4, int x_copy5, int x_copy6, int x_copy7, int x_copy8, int x_copy9)
{
  return ((((((((__inlineCall(lib(x, 0)) + __inlineCall(lib(x_copy1, 0))) + __inlineCall(lib(x_copy2, 0))) + __inlineCall(lib(x_copy3, 0))) + __inlineCall(lib(x_copy4, 0))) + __inlineCall(lib(x_copy5, 0))) + __inlineCall(lib(x_copy6, 0))) + __inlineCall(lib(x_copy7, 0))) + __inlineCall(lib(x_copy8, 0))) + __inlineCall(lib(x_copy9, 0));
}

