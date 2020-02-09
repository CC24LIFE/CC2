extern int __inlineCall(int);
int lib(int x)
{
  int ret;
  if (x > 11)
    ret = 11;
  else
    ret = x - 1;

  return ret;
}

int client(int x, int x_copy1)
{
  int ret;
  if (x > __inlineCall(lib(x)))
    ret = x;
  else
    ret = __inlineCall(lib(x));

  int ret_copy1;
  if (x_copy1 > 0)
  {
    ret_copy1 = -__inlineCall(lib(-x_copy1));
  }
  else
  {
    ret_copy1 = __inlineCall(lib(x_copy1));
  }

  return ret + ret_copy1;
}

