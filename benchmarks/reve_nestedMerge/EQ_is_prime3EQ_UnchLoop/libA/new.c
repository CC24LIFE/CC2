extern int __inlineCall(int);

int foo(int a, int b)
{
  int c = 0;
  for (int i = 0; i < a; ++i)
  {
    c = c + b;
  }

  return c + 1;
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
    INLINED_RET_0 = __inlineCall(foo(5, 900));
    ret = INLINED_RET_0;
  }

  return ret;
}


