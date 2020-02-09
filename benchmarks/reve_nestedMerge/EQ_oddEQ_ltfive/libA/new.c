extern int __inlineCall(int);

int lib(int x)
{
  int ret;
  if (x < 0)
    ret = 0;
  else
    ret = x;

  return ret;
}

int client(int x)
{
  int INLINED_RET_0;
  int ret;
  int x_copy0 = x;
  int ret_copy0;
  if (x_copy0 < 0)
  {
    ret_copy0 = (-__inlineCall(lib((-x_copy0) * 5))) / 5;
  }
  else
  {
    ret_copy0 = (__inlineCall(lib((x_copy0 + 1) * 5)) / 5) - 1;
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


