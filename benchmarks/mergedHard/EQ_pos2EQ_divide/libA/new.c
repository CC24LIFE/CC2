int lib(int x)
{
  int ret;
  if (x < 0)
  {
    ret = -x;
  }
  else
  {
    while (x >= 0)
    {
      x = x;
    }

    ret = x;
  }

  return ret;
}

int client(int x, int c_copy1, int d_copy1)
{
  int ret;
  if (x > 0)
  {
    ret = -lib(-x);
  }
  else
  {
    ret = lib(x);
  }

  int ret_copy1;
  if (d_copy1 == 0)
  {
    ret_copy1 = 0;
  }
  else
  {
    ret_copy1 = lib(c_copy1);
  }

  return ret + ret_copy1;
}

