extern int __inlineCall(int);

int lib(int x)
{
  return x % 6;
}

int client(int x)
{
  int INLINED_RET_1;
  int INLINED_RET_0;
  int ret;
  if (x > 0)
  {
    int x_copy0 = -x;
    int ret_copy0;
    x_copy0 = (x_copy0 * 5) * 6;
    if (__inlineCall(lib(x_copy0)) == 0)
    {
      ret_copy0 = 1;
    }
    else
    {
      ret_copy0 = 0;
    }

    INLINED_RET_0 = ret_copy0;
    ret = -INLINED_RET_0;
  }
  else
  {
    int x_copy1 = x;
    int ret_copy1;
    x_copy1 = (x_copy1 * 5) * 6;
    if (__inlineCall(lib(x_copy1)) == 0)
    {
      ret_copy1 = 1;
    }
    else
    {
      ret_copy1 = 0;
    }

    INLINED_RET_1 = ret_copy1;
    ret = INLINED_RET_1;
  }

  return ret;
}


