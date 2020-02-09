extern int __inlineCall(int);
int foo(int a, int b);
int clientmain(int n_copy1)
{
  int i_copy1 = 0;
  int sum_copy1 = 0;
  while (i_copy1 <= n_copy1)
  {
    if (__inlineCall(foo(i_copy1, i_copy1)) == 0)
    {
      sum_copy1 += i_copy1;
    }

    i_copy1++;
  }

  return __inlineCall(foo(5, 900)) + sum_copy1;
}

int foo(int a, int b)
{
  int c = a + b;
  return c;
}

