extern int __inlineCall(int);
int lib(int x)
{
  int ret = x;
  if (x < 0)
  {
    ret = -x;
  }

  return ret;
}

int clientmain(int x_copy1)
{
  int ret_copy1 = -x_copy1;
  if (x_copy1 < 0)
  {
    ret_copy1 = __inlineCall(lib(x_copy1));
  }

  return __inlineCall(lib(5)) + ret_copy1;
}

