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

int client(int n)
{
  int INLINED_RET_0;
  int INLINED_RET_1;
  int i = 0;
  int sum = 0;
  while (i <= n)
  {
    int x_copy0 = i;
    INLINED_RET_0 = lib(x_copy0, 0);
    if (INLINED_RET_0 == 0)
    {
      sum += i;
    }

    i++;
  }

  int x_copy1 = sum;
  INLINED_RET_1 = lib(x_copy1, 0);
  return INLINED_RET_1 == 0;
}


