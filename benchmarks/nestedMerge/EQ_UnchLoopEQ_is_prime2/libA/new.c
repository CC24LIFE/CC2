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
        ret = x == primes[i];
        done = 1;
      }

    }

  }

  return ret;
}

int clientmain()
{
  int INLINED_RET_0;
  int x_copy0 = 5;
  int ret_copy0;
  if (x_copy0 < 19)
  {
    ret_copy0 = lib(20, 1);
  }
  else
  {
    ret_copy0 = lib(x_copy0, 1);
  }

  INLINED_RET_0 = ret_copy0;
  return INLINED_RET_0;
}


