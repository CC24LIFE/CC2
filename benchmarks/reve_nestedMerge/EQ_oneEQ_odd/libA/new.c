extern int __inlineCall(int);

int lib(int x)
{
  return (x + 1) % 2;
}

int client(int x)
{
  int INLINED_RET_0;
  int INLINED_RET_1;
  int ret;
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
  if (x > INLINED_RET_0)
  {
    ret = x;
  }
  else
  {
    int x_copy1 = x;
    int ret_copy1;
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


