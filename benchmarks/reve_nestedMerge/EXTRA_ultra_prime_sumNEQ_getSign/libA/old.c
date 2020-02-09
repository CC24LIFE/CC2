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

int client(int n)
{
  int INLINED_RET_0;
  int INLINED_RET_1;
  int i = 0;
  int sum = 0;
  while (i <= n)
  {
    int x_copy0 = i;
    INLINED_RET_0 = __inlineCall(lib(x_copy0));
    if (INLINED_RET_0 == 0)
    {
      sum += i;
    }

    i++;
  }

  int x_copy1 = sum;
  INLINED_RET_1 = __inlineCall(lib(x_copy1));
  return INLINED_RET_1 == 0;
}


