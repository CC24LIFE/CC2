extern int __inlineCall(int);
int foo(int a, int b);
int client(int x)
{
  int ret = x;
  if (x > 0)
  {
    ret = __inlineCall(foo(x, x));
  }

  return ret + __inlineCall(foo(5, 900));
}

int foo(int a, int b)
{
  int c = 1;
  for (int i = 0; i < a; ++i)
  {
    c = c + b;
  }

  return c;
}

