int lib(int x)
{
  int ret;
  if (x > 11)
    ret = 11;
  else
    ret = x - 1;

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
    if ((x_copy0 < (-100)) || (x_copy0 > 100))
    {
      ret_copy0 = x_copy0;
    }
    else
    {
      if (x_copy0 > lib(x_copy0))
      {
        ret_copy0 = x_copy0;
      }
      else
      {
        ret_copy0 = lib(x_copy0);
      }

    }

    INLINED_RET_0 = ret_copy0;
    ret = INLINED_RET_0;
  }

  return ret;
}


