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

int clientmain()
{
  int INLINED_RET_0;
  int x_copy0 = 5;
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
  return INLINED_RET_0;
}


