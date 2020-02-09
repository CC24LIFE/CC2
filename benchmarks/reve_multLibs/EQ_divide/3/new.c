extern int __inlineCall(int);
int lib(int x, int y)
{
  if (y == 0)
  {
    return 0;
  }

  return x / y;
}

int client(int c, int d, int c_copy1, int d_copy1, int c_copy2, int d_copy2)
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
  if (d_copy1 == 0)
  {
    ret_copy1 = 0;
  }
  else
  {
    ret_copy1 = __inlineCall(lib(c_copy1, d_copy1));
  }

  int ret_copy2;
  if (d_copy2 == 0)
  {
    ret_copy2 = 0;
  }
  else
  {
    ret_copy2 = __inlineCall(lib(c_copy2, d_copy2));
  }

  return (ret + ret_copy1) + ret_copy2;
}

