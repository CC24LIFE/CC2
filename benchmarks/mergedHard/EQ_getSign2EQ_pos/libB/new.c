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

int client(int x, int x_copy1)
{
  int ret = x;
  if (x > 0)
  {
    ret = lib(x);
  }

  int ret_copy1;
  if (x_copy1 > 0)
  {
    ret_copy1 = -lib(-x_copy1);
  }
  else
  {
    ret_copy1 = lib(x_copy1);
  }

  return ret + ret_copy1;
}

