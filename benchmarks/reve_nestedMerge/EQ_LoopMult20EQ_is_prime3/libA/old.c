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

int clientmain(int x)
{
  int INLINED_RET_0;
  int ret = 0;
  if ((x >= 18) && (x < 22))
  {
    int x_copy0 = x;
    int ret_copy0;
    int primes_copy0[8] = {2, 3, 5, 7, 11, 13, 17, 19};
    int done_copy0 = 0;
    for (int i_copy0 = 0; i_copy0 < 8; i_copy0++)
    {
      if ((!done_copy0) && (x_copy0 == primes_copy0[i_copy0]))
      {
        ret_copy0 = 1;
        done_copy0 = 1;
      }

    }

    if (!done_copy0)
    {
      ret_copy0 = __inlineCall(lib(x_copy0, 1));
    }

    INLINED_RET_0 = ret_copy0;
    ret = INLINED_RET_0;
  }

  return ret;
}


