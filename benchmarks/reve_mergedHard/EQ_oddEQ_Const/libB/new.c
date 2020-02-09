extern int __inlineCall(int);
int foo(int a, int b);
int client(int x)
{
  int ret;
  if (__inlineCall(foo(x, x)) == 0)
  {
    ret = 1;
  }
  else
  {
    ret = 0;
  }

  return ret + __inlineCall(foo(5, 900));
}

int foo(int a, int b)
{
  const int d = 3;
  int c = b + a;
  return c + d;
}

