int lib(int x, int y)
{
  return x / y;
}

int client(int n)
{
  int INLINED_RET_1;
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

  int d_copy1 = sum;
  int c_copy1 = sum;
  int ret_copy1;
  if (d_copy1 == 0)
  {
    ret_copy1 = 0;
  }
  else
  {
    ret_copy1 = lib(c_copy1, d_copy1);
  }

  INLINED_RET_1 = ret_copy1;
  return INLINED_RET_1 == 0;
}


