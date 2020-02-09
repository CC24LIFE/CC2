int lib(int x)
{
  return x % 5;
}

int clientmain()
{
  int INLINED_RET_0;
  int x_copy0 = 5;
  int ret_copy0;
  if ((x_copy0 < (-100)) || (x_copy0 > 100))
  {
    ret_copy0 = x_copy0;
  }
  else
  {
    x_copy0 = (x_copy0 * 5) * 6;
    if (lib(x_copy0) == 0)
    {
      ret_copy0 = 1;
    }
    else
    {
      ret_copy0 = 0;
    }

  }

  INLINED_RET_0 = ret_copy0;
  return INLINED_RET_0;
}


