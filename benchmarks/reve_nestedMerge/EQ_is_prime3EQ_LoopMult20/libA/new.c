extern int __inlineCall(int);

int foo(int a, int b)
{
  int c = 0;
  for (int i = 1; i <= a; ++i)
    c += b;

  return c;
}

int client(int x)
{
  int INLINED_RET_0;
  int ret;
  int primes[8] = {2, 3, 5, 7, 11, 13, 17, 19};
  int done = 0;
  for (int i = 0; i < 8; i++)
  {
    if ((!done) && (x == primes[i]))
    {
      ret = 1;
      done = 1;
    }

  }

  if (!done)
  {
    int x_copy0 = x;
    int ret_copy0 = 0;
    if ((x_copy0 >= 18) && (x_copy0 < 22))
    {
      ret_copy0 = __inlineCall(foo(x_copy0, 20));
    }

    INLINED_RET_0 = ret_copy0;
    ret = INLINED_RET_0;
  }

  return ret;
}


