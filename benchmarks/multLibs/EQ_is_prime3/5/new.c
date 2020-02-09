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

int client(int x, int x_copy1, int x_copy2, int x_copy3, int x_copy4)
{
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
    ret = lib(x, 1);

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

  int ret_copy2;
  int primes_copy2[8] = {2, 3, 5, 7, 11, 13, 17, 19};
  int done_copy2 = 0;
  for (int i_copy2 = 0; i_copy2 < 8; i_copy2++)
  {
    if ((!done_copy2) && (x_copy2 == primes_copy2[i_copy2]))
    {
      ret_copy2 = 1;
      done_copy2 = 1;
    }

  }

  if (!done_copy2)
    ret_copy2 = lib(x_copy2, 1);

  int ret_copy3;
  int primes_copy3[8] = {2, 3, 5, 7, 11, 13, 17, 19};
  int done_copy3 = 0;
  for (int i_copy3 = 0; i_copy3 < 8; i_copy3++)
  {
    if ((!done_copy3) && (x_copy3 == primes_copy3[i_copy3]))
    {
      ret_copy3 = 1;
      done_copy3 = 1;
    }

  }

  if (!done_copy3)
    ret_copy3 = lib(x_copy3, 1);

  int ret_copy4;
  int primes_copy4[8] = {2, 3, 5, 7, 11, 13, 17, 19};
  int done_copy4 = 0;
  for (int i_copy4 = 0; i_copy4 < 8; i_copy4++)
  {
    if ((!done_copy4) && (x_copy4 == primes_copy4[i_copy4]))
    {
      ret_copy4 = 1;
      done_copy4 = 1;
    }

  }

  if (!done_copy4)
    ret_copy4 = lib(x_copy4, 1);

  return (((ret + ret_copy1) + ret_copy2) + ret_copy3) + ret_copy4;
}

