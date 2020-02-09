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

int client(int n)
{
  int INLINED_RET_0;
  int i = 0;
  int sum = 0;
  while (i <= n)
  {
    int n_copy0 = i;
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

    INLINED_RET_0 = __inlineCall(lib(sum_copy0)) == 0;
    if (INLINED_RET_0 == 0)
    {
      sum += i;
    }

    i++;
  }

  return sum;
}


