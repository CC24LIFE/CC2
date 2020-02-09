extern int __inlineCall(int);
int foo(int a, int b);
int client(int n)
{
  int i = 0;
  int sum = 0;
  while (i <= n)
  {
    if (__inlineCall(foo(i, i)) == 0)
    {
      sum += i;
    }

    i++;
  }

  return sum + __inlineCall(foo(5, 900));
}

int foo(int a, int b)
{
  int c = b + a;
  return c;
}

