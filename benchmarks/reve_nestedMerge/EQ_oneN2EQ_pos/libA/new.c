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

int client(int x)
{
  int INLINED_RET_1;
  int INLINED_RET_0;
  int ret;
  int x_copy0 = x;
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
  if (x > INLINED_RET_0)
  {
    ret = x;
  }
  else
  {
    int x_copy1 = x;
    int ret_copy1;
    if (x_copy1 > 0)
    {
      ret_copy1 = -__inlineCall(lib(-x_copy1));
    }
    else
    {
      ret_copy1 = __inlineCall(lib(x_copy1));
    }

    INLINED_RET_1 = ret_copy1;
    ret = INLINED_RET_1;
  }

  return ret;
}


