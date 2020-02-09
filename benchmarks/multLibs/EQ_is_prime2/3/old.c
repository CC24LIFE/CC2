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

int client(int x, int x_copy1, int x_copy2)
{
  int ret;
  if (x < 19)
  {
    ret = lib(20, 1);
  }
  else
  {
    ret = lib(x, 1);
  }

  int ret_copy1;
  if (x_copy1 < 19)
  {
    ret_copy1 = lib(20, 1);
  }
  else
  {
    ret_copy1 = lib(x_copy1, 1);
  }

  int ret_copy2;
  if (x_copy2 < 19)
  {
    ret_copy2 = lib(20, 1);
  }
  else
  {
    ret_copy2 = lib(x_copy2, 1);
  }

  return (ret + ret_copy1) + ret_copy2;
}

