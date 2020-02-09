extern int __inlineCall(int);
int lib(int x)
{
  int ret;
  if (x > 10)
    ret = 12;
  else
    ret = x + 1;

  return ret;
}

int client(int x, int n_copy1)
{
  int ret;
  if (x > __inlineCall(lib(x)))
    ret = x;
  else
    ret = __inlineCall(lib(x));

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

  return ret + sum_copy1;
}

