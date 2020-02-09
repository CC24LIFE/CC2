extern int __inlineCall(int);
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
  int ret_copy1;
  if (x_copy1 > 0)
  {
    ret_copy1 = -__inlineCall(lib(-x_copy1));
  }
  else
  {
    ret_copy1 = __inlineCall(lib(x_copy1));
  }

  return __inlineCall(lib(x)) + ret_copy1;
}

