extern int __inlineCall(int);
int lib(int x)
{
  int counter = 0;
  while ((x % 2) == 0)
  {
    x = x / 2;
    counter++;
  }

  return counter;
}

int client(int x, int x_copy1)
{
  int ret;
  if (__inlineCall(lib(x)) == 0)
  {
    ret = 1;
  }
  else
  {
    ret = 0;
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
    ret_copy1 = __inlineCall(lib(x_copy1));

  return ret + ret_copy1;
}

