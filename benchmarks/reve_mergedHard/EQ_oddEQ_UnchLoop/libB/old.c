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
  int c = 1;
  for (int i = 0; i < a; ++i)
  {
    c = c + b;
  }

  return c;
}

