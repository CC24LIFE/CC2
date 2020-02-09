extern int __inlineCall(int);
int lib(int x)
{
  return (x + 1) % 2;
}

int client(int x, int c_copy1, int d_copy1)
{
  int ret;
  if (__inlineCall(lib(x)) == 0)
  {
    ret = 1;
  }
  else
  {
    ret = 0;
  }

  int ret_copy1;
  if (d_copy1 == 0)
  {
    ret_copy1 = 0;
  }
  else
  {
    ret_copy1 = __inlineCall(lib(c_copy1));
  }

  return ret + ret_copy1;
}

