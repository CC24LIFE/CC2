extern int __inlineCall(int);

int foo(int a, int b)
{
  const int d = 3;
  int c = b + a;
  return c + d;
}

int clientmain(int x)
{
  int INLINED_RET_0;
  int ret = 0;
  if ((x >= 18) && (x < 22))
  {
    INLINED_RET_0 = __inlineCall(foo(5, 900));
    ret = INLINED_RET_0;
  }

  return ret;
}


