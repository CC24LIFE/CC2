int lib(int x, int y)
{
  if (y == 0)
  {
    return 0;
  }

  return x / y;
}

int clientmain(int x)
{
  int INLINED_RET_0;
  int ret = 0;
  if ((x >= 18) && (x < 22))
  {
    int d_copy0 = 20;
    int c_copy0 = x;
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
    ret = INLINED_RET_0;
  }

  return ret;
}


