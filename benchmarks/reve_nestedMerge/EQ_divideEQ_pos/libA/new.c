extern int __inlineCall(int);

int lib(int x)
{
  int ret;
  if (x < 0)
  {
    ret = -x;
  }
  else
  {
    ret = x;
  }

  return ret;
}

int client(int c, int d)
{
  int INLINED_RET_0;
  int ret;
  if (d == 0)
  {
    ret = 0;
  }
  else
  {
    int x_copy0 = c;
    int ret_copy0;
    if (x_copy0 > 0)
    {
      ret_copy0 = -__inlineCall(lib(-x_copy0));
    }
    else
    {
      ret_copy0 = __inlineCall(lib(x_copy0));
    }

    INLINED_RET_0 = ret_copy0;
    ret = INLINED_RET_0;
  }

  return ret;
}


