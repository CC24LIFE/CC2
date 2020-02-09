int lib(int x)
{
  int counter = 0;
  while (x < 0)
  {
    x++;
    counter++;
  }

  return counter;
}

int client(int x, int x_copy1)
{
  int ret;
  if (x > 0)
  {
    ret = -lib(-x);
  }
  else
  {
    ret = lib(x);
  }

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
    ret_copy1 = lib(x_copy1);

  return ret + ret_copy1;
}

