extern int __inlineCall(int);
int lib(int x, int y)
{
  return x / y;
}

int client(int n, int c_copy1, int d_copy1)
{
  int i = 0;
  int sum = 0;
  while (i <= n)
  {
    if (__inlineCall(lib(i, i)) == 0)
    {
      sum += i;
    }

    i++;
  }

  int ret_copy1;
  if (d_copy1 == 0)
  {
    ret_copy1 = 0;
  }
  else
  {
    ret_copy1 = __inlineCall(lib(c_copy1, d_copy1));
  }

  return (__inlineCall(lib(sum, sum)) == 0) + ret_copy1;
}

