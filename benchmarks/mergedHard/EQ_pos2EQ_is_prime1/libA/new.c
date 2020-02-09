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

int client(int x, int x_copy1)
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

  return ret + lib(x_copy1);
}

