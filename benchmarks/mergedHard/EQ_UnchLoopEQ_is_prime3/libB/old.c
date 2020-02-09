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

int clientmain(int x_copy1)
{
  int ret_copy1;
  int primes_copy1[8] = {2, 3, 5, 7, 11, 13, 17, 19};
  int done_copy1 = 0;
  for (int i_copy1 = 0; i_copy1 < 8; i_copy1++)
  {
    if ((!done_copy1) && (x_copy1 == primes_copy1[i_copy1]))
    {
      ret_copy1 = 1;
      done_copy1 = 1;
    }

  }

  if (!done_copy1)
    ret_copy1 = lib(x_copy1, 1);

  return lib(5, 900) + ret_copy1;
}

