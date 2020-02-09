extern int __inlineCall(int);
int lib(int x, int y)
{
  if (y == 0)
  {
    return 0;
  }

  return x / y;
}

int client(int x, int c_copy1, int d_copy1)
{
  int ret;
  if (x > 0)
  {
    ret = -__inlineCall(lib(-x, -x));
  }
  else
  {
    ret = __inlineCall(lib(x, x));
  }

  int ret_copy1;
  if (d_copy1 == 0)
  {
    ret_copy1 = 0;
  }
  else
  {
    ret_copy1 = __inlineCall(lib(c_copy1, d_copy1));
  }

  return ret + ret_copy1;
}

