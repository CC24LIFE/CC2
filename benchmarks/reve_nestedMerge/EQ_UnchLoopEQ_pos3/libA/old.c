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
    int counter = 0;
    while (x > 0)
    {
      x += 1;
      counter += 1;
    }

    ret = counter;
  }

  return ret;
}

int clientmain()
{
  int INLINED_RET_0;
  int x_copy0 = 5;
  int ret_copy0 = -x_copy0;
  if (x_copy0 < 0)
  {
    ret_copy0 = __inlineCall(lib(x_copy0));
  }

  INLINED_RET_0 = ret_copy0;
  return INLINED_RET_0;
}


