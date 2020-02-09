extern int __inlineCall(int);
int foo(int a, int b);
int client(int x)
{
  int ret;
  if (x > 0)
  {
    ret = -__inlineCall(foo(-x, -x));
  }
  else
  {
    ret = __inlineCall(foo(x, x));
  }

  return ret + __inlineCall(foo(5, 900));
}

int foo(int a, int b)
{
  int c = a + b;
  return c + 3;
}

