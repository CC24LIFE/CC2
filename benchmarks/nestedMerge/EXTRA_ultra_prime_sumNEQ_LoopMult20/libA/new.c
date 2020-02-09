int foo(int a, int b)
{
  int c = 0;
  for (int i = 1; i <= a; ++i)
    c += b;

  return c;
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
    int ret_copy0 = 0;
    if ((x_copy0 >= 18) && (x_copy0 < 22))
    {
      ret_copy0 = foo(x_copy0, 20);
    }

    INLINED_RET_0 = ret_copy0;
    if (INLINED_RET_0 == 0)
    {
      sum += i;
    }

    i++;
  }

  int x_copy1 = sum;
  int ret_copy1 = 0;
  if ((x_copy1 >= 18) && (x_copy1 < 22))
  {
    ret_copy1 = foo(x_copy1, 20);
  }

  INLINED_RET_1 = ret_copy1;
  return INLINED_RET_1 == 0;
}


