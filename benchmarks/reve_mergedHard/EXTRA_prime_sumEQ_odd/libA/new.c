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
  if (__inlineCall(lib(x_copy1)) == 0)
  {
    ret_copy1 = 1;
  }
  else
  {
    ret_copy1 = 0;
  }

  return sum + ret_copy1;
}

