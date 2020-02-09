extern int __inlineCall(int);
int lib(int x)
{
  return x % 5;
}

int client(int n, int x_copy1)
{
  int i = 0;
  int sum = 0;
  while (i <= n)
  {
    if (__inlineCall(lib(i)) == 0)
    {
      sum += i;
    }

    i++;
  }

  int ret_copy1;
  x_copy1 = (x_copy1 * 5) * 6;
  if (__inlineCall(lib(x_copy1)) == 0)
  {
    ret_copy1 = 1;
  }
  else
  {
    ret_copy1 = 0;
  }

  return (__inlineCall(lib(sum)) == 0) + ret_copy1;
}

