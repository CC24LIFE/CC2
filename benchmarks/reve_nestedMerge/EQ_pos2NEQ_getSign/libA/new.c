extern int __inlineCall(int);

int lib(int x)
{
  int ret;
  if (x <= 0)
    ret = -1;
  else
    ret = 1;

  return ret;
}

int client(int x)
{
  int INLINED_RET_0;
  int INLINED_RET_1;
  int ret;
  if (x > 0)
  {
    int x_copy0 = -x;
    INLINED_RET_0 = __inlineCall(lib(x_copy0));
    ret = -INLINED_RET_0;
  }
  else
  {
    int x_copy1 = x;
    INLINED_RET_1 = __inlineCall(lib(x_copy1));
    ret = INLINED_RET_1;
  }

  return ret;
}


