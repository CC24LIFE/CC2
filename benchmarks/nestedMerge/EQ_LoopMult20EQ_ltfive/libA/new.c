int lib(int x)
{
  int ret;
  if (x < 0)
    ret = 0;
  else
    ret = x;

  return ret;
}

int clientmain(int x)
{
  int INLINED_RET_0;
  int ret = 0;
  if ((x >= 18) && (x < 22))
  {
    int x_copy0 = x;
    int ret_copy0;
    if (x_copy0 < 0)
    {
      ret_copy0 = (-lib((-x_copy0) * 5)) / 5;
    }
    else
    {
      ret_copy0 = (lib((x_copy0 + 1) * 5) / 5) - 1;
    }

    INLINED_RET_0 = ret_copy0;
    ret = INLINED_RET_0;
  }

  return ret;
}


