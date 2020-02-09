int lib(int x, int y)
{
  if (y == 0)
  {
    return 0;
  }

  return x / y;
}

int client(int x)
{
  int INLINED_RET_1;
  int INLINED_RET_0;
  int ret;
  if (x > 0)
  {
    int d_copy0 = -x;
    int c_copy0 = -x;
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
    ret = -INLINED_RET_0;
  }
  else
  {
    int d_copy1 = x;
    int c_copy1 = x;
    int ret_copy1;
    if (d_copy1 == 0)
    {
      ret_copy1 = 0;
    }
    else
    {
      ret_copy1 = lib(c_copy1, d_copy1);
    }

    INLINED_RET_1 = ret_copy1;
    ret = INLINED_RET_1;
  }

  return ret;
}


