extern int __inlineCall(int);
int lib(int x, int y)
{
  if (y == 0)
  {
    return 0;
  }

  return x / y;
}

int client(int c, int d, int x_copy1)
{
  int ret;
  if (d == 0)
  {
    ret = 0;
  }
  else
  {
    ret = __inlineCall(lib(c, d));
  }

  int ret_copy1;
  if (x_copy1 > 0)
  {
    ret_copy1 = -__inlineCall(lib(-x_copy1, -x_copy1));
  }
  else
  {
    ret_copy1 = __inlineCall(lib(x_copy1, x_copy1));
  }

  return ret + ret_copy1;
}

