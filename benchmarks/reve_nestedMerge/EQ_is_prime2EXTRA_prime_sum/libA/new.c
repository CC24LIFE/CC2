extern int __inlineCall(int);

int lib(int a)
{
  int i = 2;
  int count = 0;
  while (i < a)
  {
    if ((a % i) != 0)
    {
      count = 1;
    }

    i++;
  }

  return count;
}

int client(int x)
{
  int INLINED_RET_0;
  int INLINED_RET_1;
  int ret;
  if (x < 19)
  {
    int n_copy0 = 20;
    int i_copy0 = 0;
    int sum_copy0 = 0;
    while (i_copy0 <= n_copy0)
    {
      if (__inlineCall(lib(i_copy0)) == 0)
      {
        sum_copy0 += i_copy0;
      }

      i_copy0++;
    }

    INLINED_RET_0 = sum_copy0;
    ret = INLINED_RET_0;
  }
  else
  {
    int n_copy1 = x;
    int i_copy1 = 0;
    int sum_copy1 = 0;
    while (i_copy1 <= n_copy1)
    {
      if (__inlineCall(lib(i_copy1)) == 0)
      {
        sum_copy1 += i_copy1;
      }

      i_copy1++;
    }

    INLINED_RET_1 = sum_copy1;
    ret = INLINED_RET_1;
  }

  return ret;
}


