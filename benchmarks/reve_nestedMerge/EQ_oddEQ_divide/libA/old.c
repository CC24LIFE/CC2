extern int __inlineCall(int);

int lib(int x, int y)
{
  return x / y;
}

int client(int x)
{
  int INLINED_RET_0;
  int ret;
  int d_copy0 = x;
  int c_copy0 = x;
  int ret_copy0;
  if (d_copy0 == 0)
  {
    ret_copy0 = 0;
  }
  else
  {
    ret_copy0 = __inlineCall(lib(c_copy0, d_copy0));
  }

  INLINED_RET_0 = ret_copy0;
  if (INLINED_RET_0 == 0)
  {
    ret = 1;
  }
  else
  {
    ret = 0;
  }

  return ret;
}


