extern int __inlineCall(int);

int lib(int x)
{
  int ret;
  if (x < 5)
    ret = 5;
  else
    ret = x;

  return ret;
}

int client(int n)
{
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
      if (x_copy0 < 0)
      {
        ret_copy0 = (-__inlineCall(lib((-x_copy0) * 5))) / 5;
      }
      else
      {
        ret_copy0 = (__inlineCall(lib((x_copy0 + 1) * 5)) / 5) - 1;
      }

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


