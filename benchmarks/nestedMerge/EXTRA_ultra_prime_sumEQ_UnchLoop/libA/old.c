int foo(int a, int b)
{
  int c = 1;
  for (int i = 0; i < a; ++i)
  {
    c = c + b;
  }

  return c;
}

int client(int n)
{
  int INLINED_RET_1;
  int INLINED_RET_0;
  int i = 0;
  int sum = 0;
  while (i <= n)
  {
    INLINED_RET_0 = foo(5, 900);
    if (INLINED_RET_0 == 0)
    {
      sum += i;
    }

    i++;
  }

  INLINED_RET_1 = foo(5, 900);
  return INLINED_RET_1 == 0;
}


