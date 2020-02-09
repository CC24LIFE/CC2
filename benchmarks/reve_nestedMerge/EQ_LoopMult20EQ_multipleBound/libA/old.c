extern int __inlineCall(int);

int lib(int x)
{
  return x % 5;
}

int clientmain(int x)
{
  int INLINED_RET_0;
  int ret = 0;
  if ((x >= 18) && (x < 22))
  {
    int x_copy0 = x;
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
    ret = INLINED_RET_0;
  }

  return ret;
}


