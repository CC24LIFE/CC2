extern int __inlineCall(int);
int foo(int a, int b);
int clientmain(int x)
{
  int ret = 0;
  if ((x >= 18) && (x < 22))
    ret = __inlineCall(foo(x, 20));

  return ret + __inlineCall(foo(5, 900));
}

int foo(int a, int b)
{
  const int d = 3;
  int c = b + a;
  return c + d;
}

