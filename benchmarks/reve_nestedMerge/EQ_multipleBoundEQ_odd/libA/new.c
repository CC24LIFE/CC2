extern int __inlineCall(int);

int lib(int x)
{
  return (x + 1) % 2;
}

int client(int x)
{
  int INLINED_RET_0;
  int ret;
  if ((x < (-100)) || (x > 100))
  {
    ret = x;
  }
  else
  {
    x = (x * 5) * 6;
    int x_copy0 = x;
    int ret_copy0;
    if (__inlineCall(lib(x_copy0)) == 0)
    {
      ret_copy0 = 1;
    }
    else
    {
      ret_copy0 = 0;
    }

    INLINED_RET_0 = ret_copy0;
    if (INLINED_RET_0 == 0)
    {
      ret = 1;
    }
    else
    {
      ret = 0;
    }

  }

  return ret;
}


