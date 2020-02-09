extern int __inlineCall(int);

int lib(int x)
{
  int ret;
  if (x == 0)
    ret = 0;
  else
    if (x < 0)
    ret = -1;
  else
    ret = 1;


  return ret;
}

int clientmain(int x)
{
  int INLINED_RET_0;
  int ret = 0;
  if ((x >= 18) && (x < 22))
  {
    int x_copy0 = x;
    INLINED_RET_0 = __inlineCall(lib(x_copy0));
    ret = INLINED_RET_0;
  }

  return ret;
}


