extern int __inlineCall(int);

int lib(int x)
{
  int ret;
  if (x > 11)
    ret = 11;
  else
    ret = x - 1;

  return ret;
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
    if (x_copy0 > __inlineCall(lib(x_copy0)))
    {
      ret_copy0 = x_copy0;
    }
    else
    {
      ret_copy0 = __inlineCall(lib(x_copy0));
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
  if (x_copy1 > __inlineCall(lib(x_copy1)))
  {
    ret_copy1 = x_copy1;
  }
  else
  {
    ret_copy1 = __inlineCall(lib(x_copy1));
  }

  INLINED_RET_1 = ret_copy1;
  return INLINED_RET_1 == 0;
}


