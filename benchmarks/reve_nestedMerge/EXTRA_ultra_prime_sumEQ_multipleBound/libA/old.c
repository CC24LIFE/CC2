extern int __inlineCall(int);

int lib(int x)
{
  return x % 5;
}

int client(int n)
{
  int INLINED_RET_1;
  int INLINED_RET_0;
  int i = 0;
  int sum = 0;
  while (i <= n)
  {
    int x_copy0 = i;
    int ret_copy0;
    if ((x_copy0 < (-100)) || (x_copy0 > 100))
    {
      ret_copy0 = x_copy0;
    }
    else
    {
      x_copy0 = (x_copy0 * 5) * 6;
      if (__inlineCall(lib(x_copy0)) == 0)
      {
        ret_copy0 = 1;
      }
      else
      {
        ret_copy0 = 0;
      }

    }

    INLINED_RET_0 = ret_copy0;
    if (INLINED_RET_0 == 0)
    {
      sum += i;
    }

    i++;
  }

  int x_copy1 = sum;
  int ret_copy1;
  if ((x_copy1 < (-100)) || (x_copy1 > 100))
  {
    ret_copy1 = x_copy1;
  }
  else
  {
    x_copy1 = (x_copy1 * 5) * 6;
    if (__inlineCall(lib(x_copy1)) == 0)
    {
      ret_copy1 = 1;
    }
    else
    {
      ret_copy1 = 0;
    }

  }

  INLINED_RET_1 = ret_copy1;
  return INLINED_RET_1 == 0;
}


