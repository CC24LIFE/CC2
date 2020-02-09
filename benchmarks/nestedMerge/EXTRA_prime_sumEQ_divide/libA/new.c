int lib(int x, int y)
{
  if (y == 0)
  {
    return 0;
  }

  return x / y;
}

int client(int n)
{
  int INLINED_RET_0;
  int i = 0;
  int sum = 0;
  while (i <= n)
  {
    int d_copy0 = i;
    int c_copy0 = i;
    int ret_copy0;
    if (d_copy0 == 0)
    {
      ret_copy0 = 0;
    }
    else
    {
      ret_copy0 = lib(c_copy0, d_copy0);
    }

    INLINED_RET_0 = ret_copy0;
    if (INLINED_RET_0 == 0)
    {
      sum += i;
    }

    i++;
  }

  return sum;
}


